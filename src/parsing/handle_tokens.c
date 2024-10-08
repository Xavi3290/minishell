/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:05:45 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/31 12:49:39 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirect_token(t_token **current, t_command *cmd, t_shell *shell,
		int type)
{
	*current = (*current)->next;
	while (*current && (*current)->type == SPACES)
		*current = (*current)->next;
	if (*current && ((*current)->type == WORD
			|| (*current)->type == DOUBLE_QUOTES
			|| (*current)->type == SINGLE_QUOTES
			|| (*current)->type == WILDC))
	{
		if (type == REDIRECT_IN)
			add_input_file(cmd, (*current)->value);
		else if (type == REDIRECT_OUT)
			add_output_file(cmd, (*current)->value, 0);
		else if (type == APPEND)
			add_output_file(cmd, (*current)->value, 1);
	}
	else
		handle_errors("syntax error: expected file after redirection",
			shell, 2);
}

void	process_redirection_file(t_token **current, t_shell *shell, int type)
{
	*current = (*current)->next;
	while (*current && (*current)->type == SPACES)
		*current = (*current)->next;
	if (*current && ((*current)->type == WORD
			|| (*current)->type == DOUBLE_QUOTES
			|| (*current)->type == SINGLE_QUOTES
			|| (*current)->type == WILDC))
	{
		if (type == REDIRECT_IN)
			create_input_file((*current)->value, shell);
		else if (type == REDIRECT_OUT)
			create_output_file((*current)->value, 0, shell);
		else if (type == APPEND)
			create_output_file((*current)->value, 1, shell);
		if ((*current)->type == WILDC)
		{
			handle_errors("*: ambiguous redirect", shell, 1);
			shell->wildc = 1;
		}
	}
	else
		handle_errors("syntax error: expected file after redirection",
			shell, 2);
}

void	handle_heredoc_token(t_command *cmd, t_token **current)
{
	char	*filename;

	filename = generate_filename();
	*current = (*current)->next;
	while (*current && (*current)->type == SPACES)
		*current = (*current)->next;
	add_heredoc_file(cmd, filename, (*current)->value, (*current)->type);
	free(filename);
}

void	handle_logical_token(t_token *current, t_command **cmd)
{
	if (current->type == AND)
		(*cmd)->and = 1;
	else
		(*cmd)->or = 1;
	(*cmd)->next = create_command();
	*cmd = (*cmd)->next;
}
