/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/23 18:00:06 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t pid = fork();
	
    if (pid == 0)
        exec_cmd(shell->env, cmd);
    else if (pid < 0)
        handle_error("minishell: fork", shell);
    else
        waitpid(pid, &(shell->last_exit_status), 0);
}

void create_pipeline(t_command *cmd, t_shell *shell)
{
    int fd[2];
    int prev_fd = -1;
    pid_t pid;
    int status;

    while (cmd)
    {
        if (cmd->next && pipe(fd) == -1)
            handle_error("minishell: pipe", shell);
        pid = fork();
        if (pid == -1)
            handle_error("minishell: fork", shell);
        if (pid == 0)
        {
            if (prev_fd != -1) // Si no es el primer comando
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    handle_error("minishell: dup2", shell);
                close(prev_fd);
            }
            if (cmd->next) // Si no es el último comando
            {
                close(fd[0]);
                if (dup2(fd[1], STDOUT_FILENO) == -1)
                    handle_error("minishell: dup2", shell);
                close(fd[1]);
            }
            exec_cmd(shell->env, cmd);
        }
        else
        {
            if (prev_fd != -1)
			{
                close(prev_fd);
				prev_fd = fd[0];
			}
			if (cmd->next)
			{
                close(fd[1]);
            	prev_fd = fd[0];
			}
			else
                prev_fd = -1;
            waitpid(pid, &status, 0);
			if (WIFEXITED(status))
                shell->last_exit_status = WEXITSTATUS(status);
        }
        cmd = cmd->next;
    }
}

static int	cmd_type(t_command *cmd, t_shell *shell)
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

void execute_commands(t_shell *shell)
{
	t_command *cmd;

	cmd = shell->commands;

    if (cmd->args && cmd->args[0] && cmd_type(cmd, shell))
    {
        if (cmd->next && cmd->next->args && cmd->next->args[0])
        {
            create_pipeline(cmd, shell);
        }
        else
        {
            execute_simple_command(cmd, shell);
        }
    }
}
