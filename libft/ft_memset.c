/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:31 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/12 21:29:35 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	char	*tmp;

	tmp = ptr;
	while (len > 0)
	{
		*tmp = c;
		tmp++;
		len--;
	}
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	char	ptr[] = "Hello world";
	char	c = 'H';
	size_t	len = 5 * sizeof(char);

	printf("%s", ft_memset(ptr, c, len));
}*/
