/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:25:18 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 11:27:28 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	i = 0;
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if (dest > src && dest < (src + n))
	{
		i = n;
		while (i > 0)
		{
			dest_ptr[i - 1] = src_ptr[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/*#include <stdio.h>
int main()
{
	char str[9] = "ABCDEF--";
	printf("Con memmove: %s\n", ft_memmove(str + 2, str, 6));
	printf("Con memcpy: %s\n", ft_memcpy(str + 2, str, 6));
	return 0;
}*/