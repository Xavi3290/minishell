/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:13:06 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 19:45:08 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(char const *s, unsigned int start, size_t len)
{
	size_t	size;

	size = 0;
	while (s[start + size])
		size++;
	if (size > len)
		size = len;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		i;
	size_t	size;

	if (start >= ft_strlen(s))
	{
		substr = malloc(1 * sizeof(char));
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	i = 0;
	size = get_size(s, start, len);
	substr = malloc((size + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	while (s[start + i] != '\0' && size-- > 0)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "Hello world";
	unsigned int	start = 4;
	size_t len = 7 * sizeof(char);
	printf("%s", ft_substr(str, start, len));
	return (0);
}*/
