/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/07 17:43:28 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  cmd_type2(t_command *cmd, t_shell *shell)
{
	if (!cmd->args)
		return (1);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(&cmd));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(shell));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd(shell));
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

int cmd_type1(t_command *cmd, t_shell *shell)
{
	if (!cmd->args)
		return (1);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(shell));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd, shell));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(shell, shell->commands));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(shell);
	return (1);
}

/*static void	handle_signals(int status)
{
	if (WIFEXITED(status))
		error_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		error_exit = WTERMSIG(status) + 128;
	}
}*/

int	create_child_process(t_command *current, int prev_fd, int *fd, \
	t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("minishell: fork", shell);
	if (pid == 0)
	{
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
		if (cmd_type1(current, shell))
			exec_cmd(shell->env, current, shell);
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
			handle_herdoc(cmd, 0, shell);
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
	if (num_commands > 1)
		create_pipeline(cmd, shell, num_commands, 0);
	else if (num_commands == 1)
	{
		if (cmd_type1(cmd, shell))
				execute_simple_command(cmd, shell);
		if (cmd->heredoc)
				unlink(cmd->input_files[0]);
	}
}
