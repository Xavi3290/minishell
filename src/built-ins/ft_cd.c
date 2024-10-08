/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:06 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/26 16:08:24 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_var(t_shell *shell, const char *var_name, \
						const char *new_value)
{
	int		i;
	char	*tmp;
	int		var_name_len;

	var_name_len = ft_strlen(var_name);
	i = 0;
	while (i < shell->env_num)
	{
		if (shell->env[i] && !ft_strncmp(shell->env[i], var_name, var_name_len))
		{
			tmp = ft_strjoin(var_name, new_value);
			free(shell->env[i]);
			shell->env[i] = tmp;
			return ;
		}
		i++;
	}
	shell->env = ft_realloc(shell->env, sizeof(char *) * shell->env_num, \
							sizeof(char *) * (shell->env_num + 2));
	if (!shell->env)
		handle_error(NULL, NULL);
	shell->env[shell->env_num] = ft_strjoin(var_name, new_value);
	shell->env_num++;
	shell->env[shell->env_num] = NULL;
}

static void	pwd_value(char *path_actual, t_shell *shell, int flag)
{
	if (!path_actual)
		path_actual = actual_path(shell);
	if (flag)
		update_env_var(shell, "PWD=", path_actual);
	else
		update_env_var(shell, "OLDPWD=", path_actual);
	free(path_actual);
}

static char	*expand_home_directory(char *path, t_shell *shell, char *oldpwd_dir)
{
	char	*expanded_path;
	char	*home_dir;

	if (path[0] == '~')
	{
		home_dir = read_env(shell, "HOME");
		if (!home_dir)
			return (NULL);
		expanded_path = malloc(ft_strlen(home_dir) + ft_strlen(path));
		if (!expanded_path)
			return (NULL);
		ft_strcpy(expanded_path, home_dir);
		ft_strcat(expanded_path, path + 1);
		return (free(home_dir), expanded_path);
	}
	else if (path[0] == '-')
	{
		if (!oldpwd_dir)
			return (printf("minishell: cd: OLDPWD not set\n"), NULL);
		printf("%s\n", oldpwd_dir);
		return (ft_strdup(oldpwd_dir));
	}
	return (ft_strdup(path));
}

int	ft_cd(t_shell *shell, t_command *cmd)
{
	char	*expanded_path;
	char	*oldpwd_dir;
	char	*tmp;

	oldpwd_dir = read_env(shell, "OLDPWD");
	pwd_value(NULL, shell, 0);
	if (cmd->num_args == 1)
	{
		tmp = read_env(shell, "HOME");
		if (chdir(tmp) == -1)
			return (printf("minishell: cd: HOME not set\n"), \
					free(oldpwd_dir), free(tmp), 1);
		pwd_value(NULL, shell, 1);
		return (free(oldpwd_dir), free(tmp), 0);
	}
	expanded_path = expand_home_directory(cmd->args[1], shell, oldpwd_dir);
	if (!expanded_path)
		return (printf("minishell: cd: %s: No such file or directory\n", \
				cmd->args[1]), free(oldpwd_dir), 1);
	if (chdir(expanded_path) == -1)
		return (printf("minishell: cd: %s: No such file or directory\n", \
				cmd->args[1]), free(oldpwd_dir), free(expanded_path), 1);
	pwd_value(NULL, shell, 1);
	return (free(oldpwd_dir), free(expanded_path), 0);
}
