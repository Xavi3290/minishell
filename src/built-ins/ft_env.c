/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:38 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/08 15:08:21 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->commands->args[1])
	{
		printf("env: \'%s\': No such file or directory\n", \
			shell->commands->args[1]);
		return (127);
	}
	while (i < shell->env_num)
	{
		if (shell->env[i] != NULL && ft_strchr(shell->env[i], '=') != 0)
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
