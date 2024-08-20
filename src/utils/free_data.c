/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:06:13 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/20 15:50:06 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	free_shell(t_shell *shell)
{
	t_command	*command;
	t_command	*next;

	free_string_array(shell->env);
	command = shell->commands;
	while (command)
	{
		next = command->next;
		free_string_array(command->args);
		free_string_array(command->input_files);
		free_string_array(command->output_files);
		free(command);
		command = next;
	}
	free_str(shell->line);
	free(shell);
}

void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
