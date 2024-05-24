/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:05:39 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 19:29:07 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!cpy)
		return (NULL);
	while (s[i] != '\0')
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "Hello world";
	printf("%s\n", ft_strdup(str));
	printf("%s\n", strdup(str));
}*/
