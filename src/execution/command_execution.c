/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/14 10:59:46 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_type2(t_command *cmd, t_shell *shell)
{
	if (!cmd->args)
		return (2);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(&cmd));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd(shell, cmd));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(shell, cmd));
	return (2);
}

int	cmd_type1(t_command *cmd, t_shell *shell)
{
	if (!cmd->args)
		return (2);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(shell, cmd));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd, shell));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(shell, cmd));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(shell, cmd));
	return (2);
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
		handle_error(NULL, NULL, 1);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		wifstuff(shell, status);
	}
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

void	execute_commands(t_shell *shell)
{
	t_command	*cmd;
	int			num_commands;
	int			num;

	cmd = shell->commands;
	num_commands = count_comands(cmd);
	if (num_commands > 1)
		create_pipeline(cmd, shell, num_commands, 0);
	else if (num_commands == 1)
	{
		num = cmd_type1(cmd, shell);
		if (num == 2)
			execute_simple_command(cmd, shell);
		else if (num != 0)
			shell->last_exit_status = num;
		if (cmd->heredoc)
			unlink(cmd->input_files[0]);
	}
}
