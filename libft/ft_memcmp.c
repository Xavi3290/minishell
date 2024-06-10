/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:14:27 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 11:56:04 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ch1;
	unsigned char	*ch2;

	i = 0;
	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (ch1[i] == ch2[i] && i < n - 1)
		i++;
	return (ch1[i] - ch2[i]);
}
/*#include <stdio.h>

int main() {
    const char *str1 = "abcdefghij";
    const char *str2 = "abcdefgxyz";
    size_t n = 7;

    int result = ft_memcmp(str1, str2, n);

    if (result < 0) {
        printf("es menor.\n");
    } else if (result == 0) {
        printf("es igual.\n");
    } else {
        printf("es mayor.\n");
    }

    return (0);
}*/