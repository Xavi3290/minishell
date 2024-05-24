/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:23:45 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 17:26:36 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = (char *) big;
	if (ft_strlen(little) == 0)
		return (res);
	while (big[i] != '\0' && len > 0)
	{
		j = 0;
		while (big[i] == little[j])
		{
			len--;
			i++;
			j++;
			if (little[j] == '\0')
				return (&res[i - j]);
			if (len == 0)
				return (NULL);
		}
		len += j - 1;
		i -= j - 1;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	const char	*largestring = "Foo Bar Baz";
	const char	*smallstring = "o Bar Ba";

	printf("%s\n", ft_strnstr(largestring, smallstring, 10));
	printf("%s\n", strnstr(largestring, smallstring, 10));
}*/
