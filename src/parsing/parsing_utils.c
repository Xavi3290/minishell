/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:37:52 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 16:20:05 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	generate_random_number(void)
{
	static unsigned int	seed;

	if (seed == 0)
		seed = 12345;
	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return (seed % 10000);
}

char	*generate_filename(void)
{
	char	*str;
	char	*num;

	num = ft_itoa(generate_random_number());
	str = ft_strjoin("/tmp/.hdoc_tmp_file", num);
	free(num);
	return (str);
}

void	handle_pipe_token(t_command **cmd)
{
	(*cmd)->next = create_command();
	*cmd = (*cmd)->next;
}
