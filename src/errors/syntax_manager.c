/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:52:09 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 17:03:39 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_unmatched_rparen(t_syntax *state)
{
	return (state->paren_count == 0 || state->last_was_operator || \
			state->last_was_pipe || state->last_was_redirect || \
			!state->last_was_word);
}

int	check_syntax(t_token *tokens, t_shell *shell)
{
	t_syntax	state;
	t_token		*current;

	state = (t_syntax){0, 0, 0, 0, 0, 0, 0, 0, 0};
	current = tokens;
	while (current)
	{
		if (!handle_general_tokens_syn(current, &state, shell))
			return (0);
		state.last_was_pipe = (current->type == PIPE);
		current = current->next;
	}
	if (state.last_was_operator || state.last_was_pipe \
		|| state.last_was_redirect || state.last_was_logical \
		|| state.paren_count > 0)
	{
		handle_errors("syntax error: unexpected end of input", shell, 2);
		return (0);
	}
	if (state.num_heredocs > 16)
		handle_errors("maximum here-document count exceeded", shell, 2);
	return (1);
}

void	handle_heredoc_token_sum(t_token *token, t_syntax *state)
{
	if (token->type == HEREDOC)
		state->num_heredocs++;
}
