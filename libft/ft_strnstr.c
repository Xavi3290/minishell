/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:19 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 11:52:39 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	char		*hys;

	i = 0;
	j = 0;
	hys = (char *)haystack;
	if (needle[j] == '\0')
		return (hys);
	while (hys[i] != '\0' && i < len)
	{
		while (hys[i + j] == needle[j] && hys[i + j] != '\0'
			&& (i + j) < len)
			j++;
		if (needle[j] == '\0')
			return (hys + i);
		i++;
		j = 0;
	}
	return (0);
}

/*#include <stdio.h>

int main(void) 
{
    const char *haystack = "lorem ipsum dolor sit amet";
    const char *needle = "dolor";
    size_t len = 15;

    char *result = ft_strnstr(haystack, needle, len);

    if (result != NULL) {
        printf("Encontrado: %s\n", result);
    } else {
        printf("No encontrado\n");
    }
	
    return (0);
}*/