/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/02 16:19:28 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
	
void	handle_herdoc(t_command *cmd, int i)
{
	char	*line;

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
			ft_putstr_fd(line, cmd->fd);
			free(line);
		}
		close(cmd->fd);
		i++;
	}

}

void	execute_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->heredoc)
			handle_herdoc(cmd, 0);
		exec_cmd(shell->env, cmd, shell);
	}
	else if (pid < 0)
		handle_error("minishell: fork", shell);
	else
		waitpid(pid, &(shell->last_exit_status), 0);
}

void	wait_for_children(pid_t *pids, int num_childrens, t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_childrens)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		i++;
	}
	free(pids);
}

int	count_comands(t_command *cmd)
{
	int			num_commands;
	t_command	*current;
	int			herdoc_count;

	num_commands = 0;
	current = cmd;
	herdoc_count = 0;
	while (current)
	{
		num_commands++;
		current = current->next;
	}
	return (num_commands);
}
