/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/25 17:41:16 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handel_herdoc(t_command *cmd)
{
	int fd;
	char *line;
	int	i;
	int j;

	i = 0;
	j = 1;
	while (cmd->input_files[i])
	{
		fd = open(cmd->input_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("\n", 1);
		while (1)
		{
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			if (ft_strncmp(line, cmd->args[j], ft_strlen(cmd->args[j])) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, fd);
			free(line);
		}
		free(cmd->args[j]);
		cmd->args[j] = NULL;
		close(fd);
		i++;
		j++;
	}
	/*if (i == 17)*/
}

void execute_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t pid = fork();
	
    if (pid == 0)
	{
		if (cmd->heredoc)
			handel_herdoc(cmd);
        exec_cmd(shell->env, cmd);
	}
    else if (pid < 0)
        handle_error("minishell: fork", shell);
    else
        waitpid(pid, &(shell->last_exit_status), 0);
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

int	create_child_process(t_command *current, int prev_fd, int *fd, \
	t_shell *shell)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		handle_error("minishell: fork", shell);
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			if (dup2(prev_fd, STDIN_FILENO) == -1)
				handle_error("minishell: dup2", shell);
			close(prev_fd);
		}
		if (current->next)
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				handle_error("minishell: dup2", shell);
			close(fd[1]);
		}
		if (cmd_type(current, shell))
			exec_cmd(shell->env, current);
		exit(127);
	}
	return (pid);
}

void wait_for_children(pid_t *pids, int num_childrens, t_shell *shell)
{
	int	status;
	int i;

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


void create_pipeline(t_command *cmd, t_shell *shell, int num_commands, int i)
{
	int fd[2];
	int prev_fd;
	t_command *current;
	pid_t *pids;

	pids = malloc(num_commands * sizeof(pid_t));
	if (!pids)
		handle_error("minishell: malloc", shell);
	prev_fd = -1;
	current = cmd;
	while (current)
	{
		if (current->heredoc)
			handel_herdoc(current);
		if (current->next && pipe(fd) == -1)
			handle_error("minishell: pipe", shell);
		pids[i++] = create_child_process(current, prev_fd, fd, shell);
		if (prev_fd != -1)
			close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		if (!current->next)
			close(fd[0]);
		current = current->next;
	}
	wait_for_children(pids, i, shell);
}

void execute_commands(t_shell *shell)
{
	t_command	*cmd;
	int			num_commands;
	t_command	*current;
	int			i; 

	cmd = shell->commands;
	num_commands = 0;
	current = cmd;
	i = 0;
	while (current)
	{
		num_commands++;
		current = current->next;
	} 
    if (cmd->args && cmd->args[0])
    {
        if (cmd->next && cmd->next->args && cmd->next->args[0])
            create_pipeline(cmd, shell, num_commands, i);
        else
		{
			if (cmd_type(cmd, shell))
            	execute_simple_command(cmd, shell);
		}
    }
}
