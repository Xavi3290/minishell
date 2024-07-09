/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:06 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/09 15:23:10 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void update_env_var(char **env, int env_num, const char *var_name, const char *new_value)
{
    int i;
    char *tmp;
    int var_name_len;

	var_name_len = ft_strlen(var_name);
	i = 0;
    while (i < env_num)
    {
        if (env[i] && !ft_strncmp(env[i], var_name, var_name_len))
        {
            tmp = ft_strjoin(var_name, new_value);
            free(env[i]);
            env[i] = tmp;
            return;
        }
		i++;
    }
    env[env_num] = ft_strjoin(var_name, new_value);
}

void pwd_value(char *path_actual, t_shell *shell, int flag)
{
    if (!path_actual)
        path_actual = actual_path();

    if (flag)
        update_env_var(shell->env, shell->env_num, "PWD=", path_actual);
    else
        update_env_var(shell->env, shell->env_num, "OLDPWD=", path_actual);

    free(path_actual);
}

int ft_cd(t_shell *shell)
{
    char *tmp;
    int i = 1;

    pwd_value(NULL, shell, 0);
    if (shell->commands->num_args == 1)
    {
        chdir(getenv("HOME"));
        pwd_value(NULL, shell, 1);
        return (0);
    }
    while (shell->commands->args[i] && ft_strchr(shell->commands->args[i], ' ') != 0)
	{
		i++;
	}
    tmp = shell->commands->args[i];
    if (!ft_strncmp(tmp, "~", 1))
        chdir(getenv("HOME"));
    else if (chdir(tmp) == -1)
    {
        put_error("minishell: cd", tmp, "No such file or directory");
        return (1);
    }
    pwd_value(NULL, shell, 1);
    return (0);
}
