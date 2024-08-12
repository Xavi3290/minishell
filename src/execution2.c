/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/12 17:41:05 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_herdoc(t_command *cmd, int i, t_shell *shell)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, handle_sig_hered);
	signal(SIGQUIT, SIG_IGN);
	while (cmd->input_files[i])
	{
		cmd->fd = open(cmd->input_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		while (1)
		{
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			if ((ft_strlen(line) - 1) == ft_strlen(cmd->delimiter[i]) && \
				ft_strncmp(line, cmd->delimiter[i], \
				ft_strlen(cmd->delimiter[i])) == 0)
			{
				free(line);
				break ;
			}
			if (*(cmd->type[i]) == WORD)
			{
				expanded = expand_variable(line, shell);
				ft_putstr_fd(expanded, cmd->fd);
				free(expanded);
			}
			else
			{
				ft_putstr_fd(line, cmd->fd);
				free(line);
			}
			free(line);
		}
		close(cmd->fd);
		i++;
	}
}

void	execute_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->heredoc)
			handle_herdoc(cmd, 0, shell);
		setup_signal_handlers();
		exec_cmd(shell->env, cmd, shell);
	}
	else if (pid < 0)
		handle_error("minishell: fork", shell);
	else
	{
		signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (status == 256)
			{
				error_exit = 1;
				shell->last_exit_status = 1;
			}
		}
		else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
		{
			error_exit = 1;
			shell->last_exit_status = 1;
		}
		handle_signals(status, shell, NULL);
	}
}

void	wait_for_children(pid_t *pids, int num_childrens, t_shell *shell)
{
	int	status;
	int	i;
	int first;

	i = 0;
	first = 1;
	while (i < num_childrens)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		handle_signals(status, shell, &first);
		i++;
	}
	free(pids);
}

int	count_comands(t_command *cmd)
{
	int			num_commands;
	t_command	*current;

	num_commands = 0;
	current = cmd;
	while (current)
	{
		num_commands++;
		current = current->next;
	}
	return (num_commands);
}
