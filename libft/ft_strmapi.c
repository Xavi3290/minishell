/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:53:52 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/13 14:44:24 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	int		i;
	char	*res;

	i = 0;
	len = ft_strlen(s);
	res = (char *) malloc((sizeof(char) * len) + 1);
	if (!res)
		return (NULL);
	while (len > 0)
	{
		res[i] = f(i, s[i]);
		len--;
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "Hello world";

	printf("%s", ft_strmapi(str, *f));
}*/
