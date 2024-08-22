/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:33:14 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/22 13:51:10 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (!str[i])
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

static int	handle_echo_flags(t_command **command, int *i)
{
	int	n;

	n = 1;
	while ((*command)->args[*i] && is_flag((*command)->args[*i]))
	{
		n = 0;
		(*i)++;
	}
	return (n);
}

int	ft_echo(t_command **command)
{
	int	n;
	int	i;

	if (!(*command)->args[1] && printf("\n"))
		return (0);
	i = 1;
	n = handle_echo_flags(command, &i);
	while (i < (*command)->num_args)
	{
		if(!ft_strcmp((*command)->args[i], "''"))
		{
			ft_putstr_fd(" ", 1);	
			i++;
		}
		ft_putstr_fd((*command)->args[i], 1);
		if (i + 1 < (*command)->num_args)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n)
		ft_putstr_fd("\n", 1);
	return (0);
}
