/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:11:20 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/14 10:59:14 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_input_file(t_command *cmd, char *file)
{
	int	i;

	i = 0;
	while (cmd->input_files && cmd->input_files[i])
		i++;
	cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i,
			sizeof(char *) * (i + 2));
	if (!cmd->input_files)
		handle_error(NULL, NULL, 1);
	cmd->input_files[i] = ft_strdup(file);
	cmd->input_files[i + 1] = NULL;
}

void	add_output_file(t_command *cmd, char *file, int append)
{
	int	i;

	i = 0;
	while (cmd->output_files && cmd->output_files[i])
		i++;
	cmd->output_files = ft_realloc(cmd->output_files, sizeof(char *) * i,
			sizeof(char *) * (i + 2));
	if (!cmd->output_files)
		handle_error(NULL, NULL, 1);
	cmd->output_files[i] = ft_strdup(file);
	cmd->output_files[i + 1] = NULL;
	cmd->append_output = append;
}

void	add_argument(t_command *cmd, char *arg)
{
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * cmd->num_args,
			sizeof(char *) * (cmd->num_args + 2));
	if (!cmd->args)
		handle_error(NULL, NULL, 1);
	cmd->args[cmd->num_args] = ft_strdup(arg);
	cmd->num_args++;
	cmd->args[cmd->num_args] = NULL;
}

void	add_type_cmd(t_command *cmd, t_token_type type)
{
	int	k;

	k = 0;
	while (cmd->type && cmd->type[k])
		k++;
	cmd->type = ft_realloc(cmd->type, sizeof(t_token_type *) * k,
			sizeof(t_token_type *) * (k + 2));
	if (!cmd->type)
		handle_error(NULL, NULL, 1);
	cmd->type[k] = malloc(sizeof(t_token_type));
	if (!cmd->type[k])
		handle_error(NULL, NULL, 1);
	*(cmd->type[k]) = type;
	cmd->type[k + 1] = NULL;
}

void	add_heredoc_file(t_command *cmd, char *file, char *delimiter,
		t_token_type type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->input_files && cmd->input_files[i])
		i++;
	while (cmd->delimiter && cmd->delimiter[j])
		j++;
	cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i,
			sizeof(char *) * (i + 2));
	if (!cmd->input_files)
		handle_error(NULL, NULL, 1);
	cmd->input_files[i] = ft_strdup(file);
	cmd->input_files[i + 1] = NULL;
	cmd->delimiter = ft_realloc(cmd->delimiter, sizeof(char *) * j,
			sizeof(char *) * (j + 2));
	if (!cmd->delimiter)
		handle_error(NULL, NULL, 1);
	cmd->delimiter[j] = ft_strdup(delimiter);
	cmd->delimiter[j + 1] = NULL;
	add_type_cmd(cmd, type);
	cmd->heredoc = 1;
}
