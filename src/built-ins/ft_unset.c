/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:14:28 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/02 15:52:43 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->env)
	{
		if (ft_strcmp(shell->env[i], shell->commands->args[i]) == 0)
		{
			free(shell->env[i]);
			j = i;
			while (j < shell->env_num - 1)
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			shell->env_num--;
			return (0);
		}
		i++;
	}
	return (-1);
}
