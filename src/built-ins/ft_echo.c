/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:33:14 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/26 16:34:52 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_echo(t_command **command)
{
	int	n;
	int	i;

	if (!(*command)->cmd && printf("\n"))
		return (0);
	n = 1;
	i = 0;
	if ((*command)->args[i] && is_flag((*command)->args[i]))
	{
		n = 0;
		i++;
	}
	while (i < (*command)->num_args)
	{
		printf("%s", (*command)->args[i]);
		i++;
	}
	if (n)
		printf("\n");
	return (0);
}
