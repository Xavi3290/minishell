/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:03:40 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/25 15:58:18 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (0);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (0);
}

/*#include <stdio.h>

int	main(void)
{
	const char *s1 = "hola";
	const char *s2 = " Ma";
	char *cat = ft_strjoin(s1, s2);

	printf("Contenido concatenado es: %s\n", cat);
	free(cat);
	return (0);
}*/