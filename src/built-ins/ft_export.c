/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:54:22 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/28 16:41:54 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env_var(t_shell *shell, char *name, char *arg)
{
	int	j;
	int	existing_var_index;

	j = 0;
	existing_var_index = -1;
	while (j < shell->env_num)
	{
		if (ft_strncmp(shell->env[j], name, ft_strlen(name)) == 0 \
			&& shell->env[j][ft_strlen(name)] == '=')
			existing_var_index = j;
		j++;
	}
	if (existing_var_index != -1)
	{
		free(shell->env[existing_var_index]);
		shell->env[existing_var_index] = ft_strdup(arg);
		return (1);
	}
	return (0);
}

int	add_env_var(t_shell *shell, char *arg)
{
	shell->env = ft_realloc(shell->env, (shell->env_num + 1) * sizeof(char *), \
		(shell->env_num + 2) * sizeof(char *));
	if (shell->env == NULL)
		return (-1);
	shell->env[shell->env_num] = ft_strdup(arg);
	shell->env_num++;
	shell->env[shell->env_num] = NULL;
	return (0);
}

char	*is_set_env(const char *arg)
{
	char	*name;
	char	*value;
	char	*equal_sign;
	char	*arg_cpy;
	char	*name_cpy;

	arg_cpy = ft_strdup(arg);
	equal_sign = ft_strchr(arg_cpy, '=');
	if (equal_sign == NULL)
	{
		free(arg_cpy);
		return (NULL);
	}
	*equal_sign = '\0';
	name = arg_cpy;
	value = equal_sign + 1;
	if (setenv(name, value, 1) != 0)
	{
		free(arg_cpy);
		return (NULL);
	}
	name_cpy = ft_strdup(name);
    free(arg_cpy);
    return (name_cpy);
}

int	ft_export(t_command *cmd, t_shell *shell)
{
	int		i;
	char	*name;

	i = 0;
	if (cmd->num_args < 2)
		return (-1);
	while (++i < cmd->num_args)
	{
		name = is_set_env(cmd->args[i]);
		if (!name)
			return (-1);
		if (!check_env_var(shell, name, cmd->args[i]))
		{
			if (add_env_var(shell, cmd->args[i]) != 0)
			{
				free(name);
				return (-1);
			}
		}
		free(name);
	}
	return (0);
}
