/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:33:14 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/25 14:43:06 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_str_special(char *str)
{
	int i;

	i = 0;
	while (str[i] != ';')
	{
		printf("%c", str[i]);
	}	
}

int	ft_echo(t_command **command)
{
	int	n;
	int	i;
	
	if (!(*command)->cmd && printf("\n"))
		return (0);
	n = 1;
	i = 0;
	while ((*command)->args[i] && is_flag((*command)->args[i]))
	{
		n = 0;
		i++;
	}
	while ((*command)->args[i])
	{
		put_str_special((*command)->args[i]);
		i++;
	}
	if (n)
		printf("\n");
	return (0);
}
