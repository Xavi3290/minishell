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
		free_str(command->input_file);
		free_str(command->output_file);
		free(command);
		command = next;
	}
	free_str(shell->line);
	free(shell);
}
