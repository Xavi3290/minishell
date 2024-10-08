/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:06:42 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/22 12:17:43 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	j = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((ss1[i] == ss2[i] && ss1[i] != '\0') && i < n)
		i++;
	if (i == n)
		i--;
	j = ss1[i] - ss2[i];
	return (j);
}*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/*#include <stdio.h>

int main(void) 
{
    const char *str1 = "saricot";
    const char *str2 = "sapel";
    size_t n = 2;

    int result = strncmp(str1, str2, n);

    if (result < 0) {
        printf("%s es lexicográficamente menor que %s.\n", str1, str2);
    } else if (result == 0) {
        printf("%s es lexicográficamente igual a %s.\n", str1, str2);
    } else {
        printf("%s es lexicográficamente mayor que %s.\n", str1, str2);
    }

    return (0);
}*/