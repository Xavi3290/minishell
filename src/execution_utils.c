/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:50:13 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/15 17:07:05 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path_list;
	char	*path;
	char	*path_final;

	i = 0;
	path_list = ft_split(get_env(env), ':');
	if (!path_list)
		print_error("mishell: command not found: ", 0, 127, cmd);
	while (path_list[i] && !ft_strchr(cmd, '/'))
	{
		path = ft_strjoin(path_list[i], "/");
		if (!path)
			print_error("mishell: command not found: ", 0, 127, cmd);
		path_final = ft_strjoin(path, cmd);
		if (!path_final)
			print_error("mishell: command not found: ", 0, 127, cmd);
		free(path);
		if (!access(path_final, X_OK | F_OK))
			return (path_final);
		free(path_final);
		i++;
	}
	free_paths(path_list);
	return (cmd);
}

static void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_l;
	char	*path;

	cmd_l = ft_split(cmd, ' ');
	if (!cmd_l)
		print_error("mishell: command not found: ", 0, 127, cmd);
	path = get_path(cmd_l[0], env);
	if (execve(path, cmd_l, env) == -1)
	{
		free_paths(cmd_l);
		print_error("mishell: command not found: ", 0, 127, cmd);
	}
	free_paths(cmd_l);
}