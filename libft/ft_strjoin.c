/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:25:06 by igarcia2          #+#    #+#             */
/*   Updated: 2024/06/06 13:42:28 by xroca-pe         ###   ########.fr       */
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
