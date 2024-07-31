/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:50:13 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/31 17:06:33 by cgaratej         ###   ########.fr       */
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

void	handle_input_redirection(t_command *cmd, char *input_file)
{
	int	fd;

	fd = open(input_file, O_RDONLY, 0644);
	if (fd == -1 || access(input_file, R_OK) == -1)
		execution_error("minishell: ", 1, 126, input_file);
	if (dup2(fd, STDIN_FILENO) == -1)
		handle_error(NULL, NULL);
	close(fd);
	if (cmd->heredoc)
		unlink(input_file);
}

void	handle_output_redirection(t_command *cmds, char *output_files)
{
	int	fd;

	if (cmds->append_output)
		fd = open(output_files, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(output_files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		execution_error("minishell: ", 1, 126, output_files);
	if (dup2(fd, STDOUT_FILENO) == -1)
		handle_error(NULL, NULL);
	close(fd);
}


void	exec_cmd(char **env, t_command *cmds)
{
	char	*path;
	int		i;

	i = 0;
	if (cmds->input_files && cmds->input_files[i])
	{
		while (cmds->input_files[i])
		{
			handle_input_redirection(cmds, cmds->input_files[i]);
			i++;
		}
	}
	if (cmds->output_files && cmds->output_files[i])
	{
		i = 0;
		while (cmds->output_files[i])
		{
			handle_output_redirection(cmds, cmds->output_files[i]);
			i++;
		}
	}
	path = get_path(cmds->args[0], env);
	if (execve(path, cmds->args, env) == -1)
		execution_error(": command not found", 0, 127, cmds->args[0]);
}
