/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:14:28 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/08 14:10:25 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_var(char ***env, int index, int *env_num)
{
	free((*env)[index]);
	while (index < *env_num - 1)
	{
		(*env)[index] = (*env)[index + 1];
		index++;
	}
	(*env)[index] = NULL;
	(*env_num)--;
}

int	compare_env_var(const char *env_var, const char *arg)
{
	char	*equal_sign;
	char	*value;
	char	*env_cpy;

	env_cpy = ft_strdup(env_var);
	equal_sign = ft_strchr(env_cpy, '=');
	if (equal_sign != NULL)
	{
		*equal_sign = '\0';
		value = equal_sign + 1;
		if (ft_strncmp(arg, value, ft_strlen(arg)) == 0)
		{
			free(env_cpy);
			return (1);
		}
	}
	else
	{
		free(env_cpy);
		if (strcmp(env_var, arg) == 0)
			return (1);
	}
	free(env_cpy);
	return (0);
}

int	process_unset_arg(t_shell *shell, const char *arg)
{
	int	i;

	i = 0;
	while (i < shell->env_num)
	{
		if (compare_env_var(shell->env[i], arg))
		{
			remove_env_var(&(shell->env), i, &(shell->env_num));
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_shell *shell, t_command *cmd)
{
	int	arg_index;
	int	result;

	arg_index = 1;
	while (arg_index < cmd->num_args)
	{
		result = process_unset_arg(shell, cmd->args[arg_index]);
		if (result != 0)
			return (0);
		arg_index++;
	}
	return (0);
}
