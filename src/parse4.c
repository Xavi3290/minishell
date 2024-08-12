/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:37:52 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/12 15:49:58 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->num_args = 0;
	cmd->input_files = NULL;
	cmd->output_files = NULL;
	cmd->delimiter = NULL;
	cmd->type = NULL;
	cmd->append_output = 0;
	cmd->heredoc = 0;
	cmd->and = 0;
	cmd->or = 0;
	cmd->parentheses = 0;
	cmd->fd = -1;
	cmd->next = NULL;
	return (cmd);
}
