/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:01:48 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/10 18:29:55 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_operators_syntax(t_token *token, t_syntax_state *state, \
			t_shell *shell)
{
	if (token->type == PIPE || token->type == AND || token->type == OR)
	{
		if (state->last_was_operator || state->last_was_pipe \
		|| state->last_was_redirect || state->last_was_logical \
		|| !state->last_was_word)
		{
			handle_error("syntax error: unexpected operator", shell);
			return (0);
		}
		state->last_was_operator = 1;
		state->last_was_word = 0;
		if (token->type == AND || token->type == OR)
			state->last_was_logical = 1;
	}
	else
	{
		state->last_was_operator = 0;
		state->last_was_logical = 0;
	}
	return (1);
}

static int	handle_redirects_syntax(t_token *token, t_syntax_state *state, \
			t_shell *shell)
{
	if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT || \
		token->type == APPEND || token->type == HEREDOC)
	{
		if (state->last_was_redirect)
		{
			handle_error("syntax error: unexpected redirect", shell);
			return (0);
		}
		state->last_was_redirect = 1;
		state->last_was_word = 0;
	}
	else
		state->last_was_redirect = 0;
	return (1);
}

static int	handle_parentheses_syntax(t_token *token, t_syntax_state *state, \
			t_shell *shell)
{
	if (token->type == LPAREN)
	{
		if (state->last_was_word || state->last_was_redirect)
		{
			handle_error("syntax error: unexpected '('", shell);
			return (0);
		}
		state->paren_count++;
		state->in_parentheses = 1;
		state->paren_opened = 1;
		state->last_was_word = 0;
	}
	else if (token->type == RPAREN)
	{
		if (is_unmatched_rparen(state))
		{
			handle_error("syntax error: unmatched ')'", shell);
			return (0);
		}
		state->paren_count--;
		if (state->paren_count == 0)
			state->in_parentheses = 0;
		state->last_was_word = 1;
	}
	return (1);
}

static int	handle_word_syntax(t_token *token, t_syntax_state *state, \
			t_shell *shell)
{
	if ((state->last_was_operator || state->last_was_pipe \
		|| state->last_was_redirect) && token->value[0] == '&')
	{
		handle_error("syntax error: unexpected '&'", shell);
		return (0);
	}
	if (state->paren_opened && state->last_was_logical)
	{
		state->paren_opened = 0;
		state->last_was_logical = 0;
	}
	state->last_was_word = 1;
	state->last_was_operator = 0;
	state->last_was_redirect = 0;
	state->last_was_pipe = 0;
	state->last_was_logical = 0;
	return (1);
}

int	handle_general_tokens_syn(t_token *token, t_syntax_state *state, \
			t_shell *shell)
{
	if (token->type == PIPE || token->type == AND || token->type == OR)
	{
		if (!handle_operators_syntax(token, state, shell))
			return (0);
	}
	else if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT || \
			token->type == APPEND || token->type == HEREDOC)
	{
		if (!handle_redirects_syntax(token, state, shell))
			return (0);
	}
	else if (token->type == LPAREN || token->type == RPAREN)
	{
		if (!handle_parentheses_syntax(token, state, shell))
			return (0);
	}
	else if (token->type == WORD)
	{
		if (!handle_word_syntax(token, state, shell))
			return (0);
	}
	return (1);
}
