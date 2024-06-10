/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:42:34 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/23 16:19:01 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	src_len;

	src_len = ft_strlen(s);
	if (!s)
		return (0);
	if (src_len < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = 0;
	if (len)
		ft_strlcpy(str, s + start, len + 1);
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	const char	*sub = "";
	char		*final = ft_substr(sub, 1, 1);
	
	printf("Contenido de la origimal: %s\n", sub);
	printf("Contenido de la sub: %s\n", final);
	free(final);
	return (0);
}*/