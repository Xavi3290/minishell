/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:50:13 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/18 15:05:09 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

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
		put_error("mishell: command not found: ", cmd, "");
	while (path_list[i] && !ft_strchr(cmd, '/'))
	{
		path = ft_strjoin(path_list[i], "/");
		if (!path)
			put_error("mishell: command not found: ", cmd, "");
		path_final = ft_strjoin(path, cmd);
		if (!path_final)
			put_error("mishell: command not found: ", cmd, "");
		free(path);
		if (!access(path_final, X_OK | F_OK))
			return (path_final);
		free(path_final);
		i++;
	}
	free_paths(path_list);
	return (cmd);
}

void	exec_cmd(char **cmd, char **env, t_shell *shell, t_command *cmds)
{
    char	*path;
	int		fd;

	if (cmds->input_files && cmds->input_files[0])
    {
        fd = open(cmds->input_files[0], O_RDONLY, 0644);
		if (access(cmds->input_files[0], R_OK) == -1)
		{
			if (fd == -1)
            	handle_error("minishell: open input file", shell);
			handle_error("minishell: permiso", shell);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
            handle_error(NULL, NULL);
        close(fd);
    }
    if (cmds->output_files && cmds->output_files[0])
    {
        if (cmds->append_output)
            fd = open(cmds->output_files[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(cmds->output_files[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            handle_error("minishell: open output file", NULL);
        if (dup2(fd, STDOUT_FILENO) == -1)
            handle_error("minishell: dup2 output file", NULL);
        close(fd);
    }
    path = get_path(cmd[0], env);
    if (execve(path, cmd, env) == -1)
    {
       execution_error(cmd[0], "command not found", shell);
    }
}
