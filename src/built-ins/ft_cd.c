/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:06 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/08 16:44:23 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_var(char **env, int env_num, const char *var_name, \
						const char *new_value)
{
	int		i;
	char	*tmp;
	int		var_name_len;

	var_name_len = ft_strlen(var_name);
	i = 0;
	while (i < env_num)
	{
		if (env[i] && !ft_strncmp(env[i], var_name, var_name_len))
		{
			tmp = ft_strjoin(var_name, new_value);
			free(env[i]);
			env[i] = tmp;
			return ;
		}
		i++;
	}
	env[env_num] = ft_strjoin(var_name, new_value);
}

void	pwd_value(char *path_actual, t_shell *shell, int flag)
{
	if (!path_actual)
		path_actual = actual_path(shell);
	if (flag)
		update_env_var(shell->env, shell->env_num, "PWD=", path_actual);
	else
		update_env_var(shell->env, shell->env_num, "OLDPWD=", path_actual);
	free(path_actual);
}

char	*expand_home_directory(const char *path)
{
	char		*expanded_path;
	const char	*home_dir;

	if (path[0] == '~')
	{
		home_dir = getenv("HOME");
		if (!home_dir)
			return (NULL);
		expanded_path = malloc(ft_strlen(home_dir) + ft_strlen(path));
		if (!expanded_path)
			return (NULL);
		ft_strcpy(expanded_path, home_dir);
		ft_strcat(expanded_path, path + 1);
		return (expanded_path);
	}
	return (ft_strdup(path));
}

int	ft_cd(t_shell *shell)
{
	char	*tmp;
	char	*expanded_path;

	pwd_value(NULL, shell, 0);
	if (shell->commands->num_args == 1)
	{
		chdir(getenv("HOME"));
		pwd_value(NULL, shell, 1);
		return (0);
	}
	tmp = shell->commands->args[1];
	expanded_path = expand_home_directory(tmp);
	if (!expanded_path)
		return (1);
	if (chdir(expanded_path) == -1)
	{
		free(expanded_path);
		return (1);
	}
	free(expanded_path);
	pwd_value(NULL, shell, 1);
	return (0);
}
