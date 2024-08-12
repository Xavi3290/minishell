/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:50:13 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/12 11:30:31 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path_list;
	char	*path;
	char	*path_final;

	i = 0;
	path_list = ft_split(get_env(env), ':');
	if (!path_list)
		execution_error(": command not found", 0, 127, cmd);
	while (path_list[i] && !ft_strchr(cmd, '/'))
	{
		path = ft_strjoin(path_list[i], "/");
		if (!path)
			execution_error(": command not found", 0, 127, cmd);
		path_final = ft_strjoin(path, cmd);
		if (!path_final)
			execution_error(": command not found", 0, 127, cmd);
		free(path);
		if (!access(path_final, X_OK | F_OK))
			return (path_final);
		free(path_final);
		i++;
	}
	free_paths(path_list);
	return (cmd);
}

void	handle_input_redirection(t_command *cmd, int num)
{
	int	fd;

	fd = open(cmd->input_files[num], O_RDONLY, 0644);
	if (fd == -1 || access(cmd->input_files[num], R_OK) == -1)
		execution_error("minishell: ", 1, 126, cmd->input_files[num]);
	if (dup2(fd, STDIN_FILENO) == -1)
		handle_error(NULL, NULL);
	close(fd);
	if (cmd->heredoc)
		unlink(cmd->input_files[num]);
}

void	handle_output_redirection(t_command *cmd, int num)
{
	int	fd;

	if (cmd->append_output)
		fd = open(cmd->output_files[num], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->output_files[num], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		execution_error("minishell: ", 1, 126, cmd->output_files[num]);
	if (dup2(fd, STDOUT_FILENO) == -1)
		handle_error(NULL, NULL);
	close(fd);
}

void	ft_redirectios(t_command *cmd)
{
	int		num_input;
	int		num_ouput;
	int		i;

	i = 0;
	num_input = ft_strlen_d(cmd->input_files) - 1;
	num_ouput = ft_strlen_d(cmd->output_files) - 1;
	while (num_input >= 0 || num_ouput >= 0)
	{
		if (cmd->input_files && num_input >= 0)
			handle_input_redirection(cmd, i);
		if (cmd->output_files && num_ouput >= 0)
			handle_output_redirection(cmd, i);
		num_input--;
		num_ouput--;
		i++;
	}
}

void	exec_cmd(char **env, t_command *cmd, t_shell *shell)
{
	char	*path;

	ft_redirectios(cmd);
	if (cmd_type2(cmd, shell) == 2)
	{
		if (!cmd->args)
			exit(1);
		path = get_path(cmd->args[0], env);
		if (execve(path, cmd->args, env) == -1)
		{
			if (path[0] == '/')
			{
				if (!access(path, X_OK | F_OK))
				{
					ft_putstr_fd("minishell: ", 2);
					execution_error(": Is a directory", 0, 126, cmd->args[0]);
				}
				ft_putstr_fd("minishell: ", 2);
				execution_error(": No such file or directory", 0, 127, \
								cmd->args[0]);
			}
			execution_error(": command not found", 0, 127, cmd->args[0]);
		}
	}
	exit(0);
}
