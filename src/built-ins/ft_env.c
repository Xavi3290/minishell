/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:38 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/02 16:25:48 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->env_num)
	{
		if (shell->env[i] != NULL && ft_strchr(shell->env[i], '=') != 0)
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (1);
}
