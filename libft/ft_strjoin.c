/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:25:06 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/13 13:15:22 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;

	i = 0;
	joined = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	if (joined == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		joined[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		joined[i] = *s2;
		s2++;
		i++;
	}
	joined[i] = '\0';
	return (joined);
}
/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "Hello ";
	char	str2[] = "world!";
	printf("%s", ft_strjoin(str, str2));
}*/
