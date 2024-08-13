/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:37:21 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/13 12:40:31 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void check_and_handle_execve_error(char *path, t_command *cmd)
{
	if (path[0] == '/')
	{
		if (!access(path, X_OK | F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			execution_error(": Is a directory", 0, 126, cmd->args[0]);
		}
		ft_putstr_fd("minishell: ", 2);
		execution_error(": No such file or directory", 0, 127, cmd->args[0]);
	}
	execution_error(": command not found", 0, 127, cmd->args[0]);
}

void handle_command_execution(char **env, t_command *cmd)
{
	char *path;

	path = get_path(cmd->args[0], env);
	if (execve(path, cmd->args, env) == -1)
		check_and_handle_execve_error(path, cmd);
}


void exec_cmd(char **env, t_command *cmd, t_shell *shell)
{
	int num;

	ft_redirectios(cmd);
	num = cmd_type2(cmd, shell);
	if (num == 2)
	{
		if (!cmd->args)
			exit(1);
		handle_command_execution(env, cmd);
	}
	else if (num != 0)
		exit(num);
	exit(0);
}