/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:14:28 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/04 16:32:04 by cgaratej         ###   ########.fr       */
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

void	ft_unset(t_shell *shell, t_command *cmd)
{
	int	i;
	int arg_index;
	char	*name_end;
	size_t	name_len;

	arg_index = 0;
	while (++arg_index < cmd->num_args)
	{
		i = -1;
		while (++i < shell->env_num)
		{
			name_end = ft_strchr(shell->env[i], '=');
			if (name_end != NULL)
			{
				name_len = name_end - shell->env[i];
				if (ft_strncmp(shell->env[i], cmd->args[arg_index], \
				name_len) == 0 && cmd->args[arg_index][name_len] == '\0')
				{
					remove_env_var(&(shell->env), i, &(shell->env_num));
					break ;
				}
			}
			else
            {
                if (strcmp(shell->env[i], cmd->args[arg_index]) == 0)
                {
                    remove_env_var(&(shell->env), i, &(shell->env_num));
                    break;
                }
            }
		}
	}
}
