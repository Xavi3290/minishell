/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:23:41 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/12 19:59:46 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;

	tmp = s;
	while (n > 0)
	{
		*tmp = 0;
		tmp++;
		n--;
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello world";
	char	str2[] = "Hello world";
	size_t	n = 5 * sizeof(char);

	bzero(str, n);
	ft_bzero(str2, n);
}*/
