/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:11:20 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/10 18:15:38 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_input_file(t_command *cmd, char *file)
{
	int	i;

	i = 0;
	while (cmd->input_files && cmd->input_files[i])
		i++;
	cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i, \
						sizeof(char *) * (i + 2));
	cmd->input_files[i] = ft_strdup(file);
	cmd->input_files[i + 1] = NULL;
}

void	add_output_file(t_command *cmd, char *file, int append)
{
	int	i;

	i = 0;
	while (cmd->output_files && cmd->output_files[i])
		i++;
	cmd->output_files = ft_realloc(cmd->output_files, sizeof(char *) * i, \
						sizeof(char *) * (i + 2));
	cmd->output_files[i] = ft_strdup(file);
	cmd->output_files[i + 1] = NULL;
	cmd->append_output = append;
}

void	add_argument(t_command *cmd, char *arg)
{
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * cmd->num_args, \
				sizeof(char *) * (cmd->num_args + 2));
	cmd->args[cmd->num_args] = ft_strdup(arg);
	cmd->num_args++;
	cmd->args[cmd->num_args] = NULL;
}

void	add_heredoc_file(t_command *cmd, char *file)
{
	int	i;

	i = 0;
	while (cmd->input_files && cmd->input_files[i])
		i++;
	cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i, \
						sizeof(char *) * (i + 2));
	cmd->input_files[i] = ft_strdup(file);
	cmd->input_files[i + 1] = NULL;
	cmd->heredoc = 1;
}

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
	cmd->append_output = 0;
	cmd->heredoc = 0;
	cmd->and = 0;
	cmd->or = 0;
	cmd->parentheses = 0;
	cmd->fd = -1;
	cmd->next = NULL;
	return (cmd);
}
