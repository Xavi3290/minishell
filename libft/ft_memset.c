/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:03:31 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/22 12:14:15 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *str, int value, size_t len)
{
	int				i;
	unsigned char	*c;

	i = 0;
	c = (unsigned char *)str;
	while (len > 0)
	{
		c[i] = value;
		i++;
		len--;
	}
	return (str);
}

/*#include <stdio.h>

int main() {
    char myString[] = "hola, mundo";

    printf("Antes de ft_memset: %s\n", myString);
    ft_memset(myString, 's', 5);
    printf("Después de ft_memset: %s\n", myString);
    return (0);
}*/