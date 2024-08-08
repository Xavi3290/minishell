/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:26:35 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/08 17:37:25 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_existing_var_indices(t_shell *shell, char *name, \
					int *existing_var_index, int *existing_var)
{
	int	j;
	int	name_len;

	*existing_var_index = -1;
	*existing_var = -1;
	name_len = ft_strlen(name);
	j = 0;
	while (j < shell->env_num)
	{
		if (ft_strncmp(shell->env[j], name, name_len) == 0)
		{
			if (shell->env[j][name_len] == '=')
				*existing_var_index = j;
			else if (shell->env[j][name_len] == '\0')
				*existing_var = j;
		}
		j++;
	}
}

int	check_env_var(t_shell *shell, char *name, char *arg)
{
	int	existing_var_index;
	int	existing_var;

	existing_var_index = -1;
	existing_var = -1;
	find_existing_var_indices(shell, name, &existing_var_index, &existing_var);
	if (existing_var_index != -1)
	{
		free(shell->env[existing_var_index]);
		shell->env[existing_var_index] = ft_strdup(arg);
		return (1);
	}
	else if (existing_var != -1)
	{
		free(shell->env[existing_var]);
		if (ft_strchr(shell->env[existing_var], '=') != 0)
			arg = ft_strdup(name);
		shell->env[existing_var] = ft_strdup(arg);
		return (1);
	}
	return (0);
}

int	add_env_var(t_shell *shell, char *arg)
{
	shell->env = ft_realloc(shell->env, (shell->env_num + 1) * sizeof(char *), \
		(shell->env_num + 2) * sizeof(char *));
	if (shell->env == NULL)
		return (1);
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
		name = ft_strdup(arg_cpy);
		free(arg_cpy);
		return (name);
	}
	*equal_sign = '\0';
	name = arg_cpy;
	value = equal_sign + 1;
	if (setenv(name, value, 1) != 0)
		return (free(arg_cpy), NULL);
	name_cpy = ft_strdup(name);
	return (free(arg_cpy), name_cpy);
}
