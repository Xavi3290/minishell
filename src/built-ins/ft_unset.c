/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:14:28 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/10 17:25:57 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_env_var(char ***env, int index, int *env_num)
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
	char	*name_end;
	size_t	name_len;

	name_end = ft_strchr(env_var, '=');
	if (name_end != NULL)
	{
		name_len = name_end - env_var;
		if (ft_strncmp(env_var, arg, name_len) == 0 && arg[name_len] == '\0')
			return (1);
	}
	else
	{
		if (strcmp(env_var, arg) == 0)
			return (1);
	}
	return (0);
}

void	process_unset_arg(t_shell *shell, const char *arg)
{
	int	i;

	i = 0;
	while (i < shell->env_num)
	{
		if (compare_env_var(shell->env[i], arg))
		{
			remove_env_var(&(shell->env), i, &(shell->env_num));
			break ;
		}
		i++;
	}
}

void	ft_unset(t_shell *shell, t_command *cmd)
{
	int	arg_index;

	arg_index = 1;
	while (arg_index < cmd->num_args)
	{
		process_unset_arg(shell, cmd->args[arg_index]);
		arg_index++;
	}
}
