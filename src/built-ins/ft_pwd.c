/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:47:13 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/18 17:54:17 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*actual_path(void)
{
	char	*s;
	char	*res;
	int		i;

	i = 0;
	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		return (0);
	if (!getcwd(s, MAXPATHLEN))
		return (0);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (0);
	i = -1;
	while (s[++i])
		res[i] = s[i]; 
	free(s);
	res[i] = '\0';
	return (res);
}

int	ft_pwd(void)
{
	char	*s;
	char	*res;
	int		i;

	i = 0;
	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		return (0);
	if (!getcwd(s, MAXPATHLEN))
		return (10);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (0);
	i = -1;
	while (s[++i])
		res[i] = s[i]; 
	free(s);
	res[i] = '\n';
	if (write(1, &res[0], i + 1) != i + 1)
		return (-1);
	return (0);
}
