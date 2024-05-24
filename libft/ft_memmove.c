/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:45:03 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 19:20:35 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dest;

	if (!dest && !src)
		return (0);
	tmp_src = (unsigned char *) src;
	tmp_dest = (unsigned char *) dest;
	if (dest <= src)
	{
		while (n--)
			*tmp_dest++ = *tmp_src++;
	}
	else if (dest > src)
	{
		tmp_dest += n - 1;
		tmp_src += n - 1;
		while (n--)
			*tmp_dest-- = *tmp_src--;
	}
	return (dest);
}

/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "Hello world";
	char	dest[] = "How are you";
	char	src2[] = "Hello world";
	char	dest2[] = "How are you";

	printf("%s\n", memmove(dest, src, 5));
	printf("%s\n", ft_memmove(dest2, src2, 5));
}*/
