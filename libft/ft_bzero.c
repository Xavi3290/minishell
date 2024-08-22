/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:34:45 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/22 12:13:33 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *str, size_t n)
{
	int				i;
	unsigned char	*c;

	i = 0;
	c = (unsigned char *)str;
	while (n > 0)
	{
		c[i] = '\0';
		i++;
		n--;
	}
}

/*#include <stdio.h>

int main(void)
{
    char myString[] = "hola, mundo";

    printf("Antes de ft_bzero: %s\n", myString);

    size_t n = 5;
    ft_bzero(myString, n);

    printf("Después de ft_bzero: %s\n", myString);

    return (0);
}*/