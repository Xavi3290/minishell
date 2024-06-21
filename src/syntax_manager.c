/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:52:09 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/21 17:57:28 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int handle_operators(t_token *token, t_syntax_state *state, t_shell *shell)
{
    if (token->type == PIPE || token->type == AND || token->type == OR)
    {
        if (state->last_was_operator || state->last_was_pipe || state->last_was_redirect || state->last_was_logical)
        {
            handle_error("syntax error: unexpected operator", shell);
            return (0);
        }
        state->last_was_operator = 1;
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

static int handle_redirects(t_token *token, t_syntax_state *state, t_shell *shell)
{
    if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT || 
        token->type == APPEND || token->type == HEREDOC)
    {
        if (state->last_was_redirect)
        {
            handle_error("syntax error: unexpected redirect", shell);
            return (0);
        }
        state->last_was_redirect = 1;
    }
    else
        state->last_was_redirect = 0;
    return (1);
}

static int handle_parentheses(t_token *token, t_syntax_state *state, t_shell *shell)
{
    if (token->type == LPAREN)
    {
        if (!state->last_was_logical && !state->in_parentheses)
        {
            handle_error("syntax error: unexpected '('", shell);
            return (0);
        }
        state->paren_count++;
        state->in_parentheses = 1;
    }
    else if (token->type == RPAREN)
    {
        if (state->paren_count == 0)
        {
            handle_error("syntax error: unmatched ')'", shell);
            return (0);
        }
        state->paren_count--;
        if (state->paren_count == 0)
            state->in_parentheses = 0;
    }
    return (1);
}

static int handle_general_tokens(t_token *token, t_syntax_state *state, t_shell *shell)
{
    if (token->type == PIPE || token->type == AND || token->type == OR)
    {
        if (!handle_operators(token, state, shell))
            return (0);
    }
    else if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT || 
             token->type == APPEND || token->type == HEREDOC)
    {
        if (!handle_redirects(token, state, shell))
            return (0);
    }
    else if (token->type == LPAREN || token->type == RPAREN)
    {
        if (!handle_parentheses(token, state, shell))
            return (0);
    }
    else if (token->type == WORD)
    {
        state->last_was_operator = 0;
        state->last_was_redirect = 0;
        state->last_was_pipe = 0;
        state->last_was_logical = 0;
    }
    return (1);
}

int check_syntax(t_token *tokens, t_shell *shell)
{
    t_syntax_state state;
    t_token *current;

    state = (t_syntax_state){0, 0, 0, 0, 0, 0};
    current = tokens;
    while (current)
    {
        if (!handle_general_tokens(current, &state, shell))
            return (0);

        state.last_was_pipe = (current->type == PIPE);
        current = current->next;
    }

    if (state.last_was_operator || state.last_was_pipe || state.last_was_redirect || state.last_was_logical || state.paren_count > 0)
    {
        handle_error("syntax error: unexpected end of input", shell);
        return (0);
    }

    return (1);
}

