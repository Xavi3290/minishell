/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:52:09 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/10 18:46:15 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_unmatched_rparen(t_syntax_state *state)
{
	return (state->paren_count == 0 || state->last_was_operator || \
			state->last_was_pipe || state->last_was_redirect || \
			!state->last_was_word);
}

int	check_syntax(t_token *tokens, t_shell *shell)
{
	t_syntax_state	state;
	t_token			*current;

	state = (t_syntax_state){0, 0, 0, 0, 0, 0, 0, 0};
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
		handle_error("syntax error: unexpected end of input", shell);
		return (0);
	}
	return (1);
}
