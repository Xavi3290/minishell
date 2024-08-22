/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:02:24 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/22 12:15:35 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ch;

	i = 0;
	ch = (char *)s;
	while (ch[i] != '\0')
	{
		if (ch[i] == (char)c)
			return (&ch[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&ch[i]);
	return (0);
}

/*#include <stdio.h>

int	main(void)
{
	char *c = ft_strchr("hola mundo", 'a');

	if (c == 0)
		printf("No se ha encontrado");
	else 
		printf("Lo ha encontrado");
	return (0);
}*/