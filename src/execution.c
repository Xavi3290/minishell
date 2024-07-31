/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/31 17:07:01 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  cmd_type(t_command *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(&cmd));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(shell));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd, shell));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(shell, shell->commands));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(shell));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(shell);
	return (1);
}

void	setup_redirection(int prev_fd, int *fd, int i, t_command *current)
{
	int	heredoc_fd;
	
    if (prev_fd != -1)
    {
        if (dup2(prev_fd, STDIN_FILENO) == -1)
            handle_error(NULL, NULL);
        close(prev_fd);
    }
    if (fd)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            handle_error(NULL, NULL);
        close(fd[1]);
    }
	if (current->heredoc)
	{
		while (current->input_files[++i])
        {
			heredoc_fd = open(current->input_files[i], O_RDONLY);
			if (heredoc_fd == -1)
				handle_error(NULL, NULL);
			if (dup2(heredoc_fd, STDIN_FILENO) == -1)
				handle_error(NULL, NULL);
			close(heredoc_fd);
        }
	}
}

int	create_child_process(t_command *current, int prev_fd, int *fd, \
	t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("minishell: fork", shell);
	if (pid == 0)
	{
		setup_redirection(prev_fd, fd, -1, current);
		if (cmd_type(current, shell))
			exec_cmd(shell->env, current);
		exit(127);
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
		handle_error("minishell: malloc", shell);
	prev_fd = -1;
	while (cmd)
	{
		if (pipe(fd) == -1)
			handle_error("minishell: pipe", shell);
		if (cmd->heredoc)
			handle_herdoc(cmd, 0);
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

void	execute_commands(t_shell *shell)
{
	t_command	*cmd;
	int			num_commands;

	cmd = shell->commands;
	num_commands = count_comands(cmd);
	if (cmd->next && cmd->next->args && cmd->next->args[0])
		create_pipeline(cmd, shell, num_commands, 0);
	else if (cmd->args && cmd->args[0])
	{
		if (cmd_type(cmd, shell))
				execute_simple_command(cmd, shell);
		if (cmd->heredoc)
				unlink(cmd->input_files[0]);
	}
	else if (cmd->heredoc)
	{
		handle_herdoc(cmd, 0);
		unlink(cmd->input_files[0]);
	}
}
