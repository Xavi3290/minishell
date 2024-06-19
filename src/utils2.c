/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:11:45 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/19 14:56:37 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_qutes(char *str)
{
	char	*tmp;
	int	j;
	int i;
	int doubles;
	int simples;

	i = -1;
	j = -1;
	doubles = 1;
	simples = 1;
	tmp = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!tmp)
		return(NULL);
	while (str[++i])
	{
		if (str[i] == 34 && simples != -1)
				doubles = -doubles;
		else if (str[i] == 39 && doubles != -1)
			simples = -simples;
		else
			tmp[++j] = str[i];
	}
	return (tmp);
}
