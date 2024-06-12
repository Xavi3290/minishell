/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:38 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/12 17:15:33 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env(t_token *cmd, t_shell *shell)
{
	int i;

	i = 0;
	if (!ft_strcmp(cmd->value, "env"))
	{
		while (i < shell->env_num)
		{
			if (shell->env[i] != NULL)
				printf("%s\n", shell->env[i]);
			i++;
		}
		return(1);
	}
	else
		return (0);
}
