/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:38 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/27 15:49:17 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	
	printf("%d\n", shell->env_num);
	while (i < shell->env_num)
	{
		if (shell->env[i] != NULL)
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (1);
}
