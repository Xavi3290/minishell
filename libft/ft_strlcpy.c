/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:16:06 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 11:51:05 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	leng;

	i = 0;
	leng = ft_strlen(src);
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (leng);
}

/*#include <stdio.h>

int main(void)
{
    char destination[20];
    const char *source = "Hello, World!";
    size_t copied_size = strlcpy(destination, source, sizeof(destination));
    printf("Contenido de la destinación: %s\n", destination);
    printf("Tamaño de la cadena copiada: %zu\n", copied_size);
    return (0);
}*/