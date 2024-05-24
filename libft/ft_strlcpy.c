/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:36:51 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 15:13:54 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while ((size - 1) > 0 && src[i] != '\0')
	{
		dst[i] = src[i];
		size--;
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*
#include <stdio.h>

int	main(void)
{
	char	src[] = "Hello world!, 3";
	char	dest[7];
	char	src2[] = "Hello world!, 3";
	char	dest2[7];


	printf("%d\n", (int) ft_strlcpy(dest, src, 7));
	printf("%d", (int) strlcpy(dest2, src2, 7));
}*/
