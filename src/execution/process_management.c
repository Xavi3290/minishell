/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/26 12:34:18 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process_logic(t_command *current, int prev_fd, int *fd, \
			t_shell *shell)
{
	int	num;

	setup_signal_handlers();
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			handle_error(NULL, NULL);
		close(prev_fd);
	}
	if (current->next)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			handle_error(NULL, NULL);
		close(fd[1]);
	}
	num = cmd_type1(current, shell);
	if (num == 2)
		exec_cmd(shell->env, current, shell);
	else if (num != 0)
		exit(num);
	exit(127);
}

static int	create_child_process(t_command *current, int prev_fd, int *fd, \
	t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error(NULL, NULL);
	if (pid == 0)
	{
		child_process_logic(current, prev_fd, fd, shell);
	}
	return (pid);
}

void	create_pipeline(t_command *cmd, t_shell *shell, int num_commands, int i)
{
	int		fd[2];
	int		prev_fd;
	pid_t	*pids;

	pids = malloc(num_commands * sizeof(pid_t));
	if (!pids)
		handle_error(NULL, NULL);
	prev_fd = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd)
	{
		if (pipe(fd) == -1)
			handle_error(NULL, NULL);
		pids[i++] = create_child_process(cmd, prev_fd, fd, shell);
		if (prev_fd != -1)
			close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		if (!cmd->next)
			close(fd[0]);
		cmd = cmd->next;
	}
	wait_for_children(pids, i, shell);
}

void	wifstuff(t_shell *shell, int status)
{
	if (WIFEXITED(status))
	{
		if (status == 256)
		{
			shell->last_exit_status = 1;
		}
	}
	else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
	{
		shell->last_exit_status = 1;
	}
	handle_signals(status, shell, NULL);
}

void	wait_for_children(pid_t *pids, int num_childrens, t_shell *shell)
{
	int	status;
	int	i;
	int	first;

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
