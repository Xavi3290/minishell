/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:06:13 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/07 16:28:05 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_str_str(char **str)
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

	free_str_str(shell->env);
	command = shell->commands;
	while (command)
	{
		next = command->next;
		free_str_str(command->args);
		free_str_str(command->input_files);
		free_str_str(command->output_files);
		free(command);
		command = next;
	}
	free_str(shell->line);
	free(shell);
}
