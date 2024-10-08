/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:37:21 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/02 11:23:01 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_command_execution(char **env, t_command *cmd);

void	exec_cmd(char **env, t_command *cmd, t_shell *shell)
{
	int	num;

	ft_redirectios(cmd, shell);
	num = cmd_type2(cmd, shell);
	if (num == 2)
	{
		if (!cmd->args && cmd->heredoc)
			exit(shell->last_exit_status);
		else if (!cmd->args)
			exit (0);
		handle_command_execution(env, cmd);
	}
	else if (num != 0)
		exit(num);
	exit(0);
}

static void	handle_command_execution(char **env, t_command *cmd)
{
	char	*path;

	path = get_path(cmd->args[0], env, -1);
	if (execve(path, cmd->args, env) == -1)
	{
		if (cmd->args[0][0] == '\0')
			execution_error("Command '' not found", 0, 127, cmd->args[0]);
		if (ft_strchr(path, '/'))
		{
			if (!access(path, X_OK | F_OK))
			{
				ft_putstr_fd("minishell: ", 2);
				execution_error(": Is a directory", 0, 126, cmd->args[0]);
			}
			ft_putstr_fd("minishell: ", 2);
			execution_error(": No such file or directory", \
						0, 127, cmd->args[0]);
		}
		execution_error(": command not found", 0, 127, cmd->args[0]);
	}
}
