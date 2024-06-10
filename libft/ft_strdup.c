/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:38:12 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 11:56:35 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*cpy;

	i = 0;
	len = ft_strlen(s1);
	cpy = (char *)malloc(sizeof(*s1) * len + 1);
	if (cpy == NULL)
		return (0);
	while (s1[i] != '\0')
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/*#include <stdio.h>

int main(void)
{
    const char *original = "Hola, Mundo!";
    
    char *duplicate = ft_strdup(original);

    if (duplicate != NULL)
	{
        printf("Cadena original: %s\n", original);
        printf("Cadena duplicada: %s\n", duplicate);
        free(duplicate);
    } else 
        printf("Error al duplicar la cadena.\n");

    return (0);
}*/