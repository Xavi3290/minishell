/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:38:16 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 11:55:50 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	i = 0;
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>

int main(void)
{
    char src[] = "hola, mundo";
    char dest[20];

    printf("Antes de ft_memcpy, src: %s\n", src);
    ft_memcpy(dest, src, ft_strlen(src));
    printf("Después de ft_memcpy, dest: %s\n", dest);

    return (0);
}*/
