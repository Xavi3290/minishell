/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:47:13 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/20 15:27:25 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_env(t_shell *shell, char *key)
{
	int		i;
	char	*arg_cpy;
	char	*equal_sign;
	char	*name;
	char	*value;

	i = 0;
	while (shell->env[i])
	{
		arg_cpy = ft_strdup(shell->env[i]);
		equal_sign = ft_strchr(arg_cpy, '=');
		*equal_sign = '\0';
		name = arg_cpy;
		if (!ft_strncmp(key, name, ft_strlen(key) + 1))
			break ;
		i++;
		free(arg_cpy);
	}
	value = ft_strdup(equal_sign + 1);
	if (!ft_strncmp(key, name, ft_strlen(key) + 1))
		free(arg_cpy);
	if (shell->env[i])
		return (value);
	return (NULL);
}

char	*actual_path(t_shell *shell)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
		return (path);
	else
	{
		path = read_env(shell, "PWD");
		if (!path)
			return (NULL);
	}
	return (path);
}

int	ft_pwd(t_shell *shell, t_command *cmd)
{
	char	*path;

	if (cmd->num_args > 1)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putendl_fd(path, 1);
		free(path);
	}
	else
	{
		path = read_env(shell, "PWD");
		if (!path)
			return (1);
		ft_putendl_fd(path, 1);
		free(path);
	}
	return (0);
}
