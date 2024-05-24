/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:49:01 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 17:15:48 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	ch;

	tmp = (unsigned char *) s;
	ch = (unsigned char) c;
	while (n > 0)
	{
		if (*tmp == ch)
			return (tmp);
		tmp++;
		n--;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	char	*result;
	char	*result2;

	result2 = memchr(str, '-1', 7);
	result = ft_memchr(str, '-1', 7);
	printf("%s\n", result);
	printf("%s\n", result2);
}*/
