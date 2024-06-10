/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:24:01 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/25 10:48:39 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*#include <stdio.h>

void	ft_myfuncion(unsigned int i, char *c)
{
	printf("%d %s\n", i, c);
}

int	main(void)
{
	char str[10] = "hola";
	ft_striteri(str, *ft_myfuncion);
	printf("%s\n", str);
	return (0);
}*/
