/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:09:58 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 19:12:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*tmp;
	unsigned char	ch;

	tmp = (char *) s;
	ch = (unsigned char) c;
	while (*tmp != '\0')
	{
		if (*tmp == ch)
			return (tmp);
		tmp++;
	}
	if (ch == '\0')
		return (tmp);
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strchr("Hello world", '\0'));
	printf("%s\n", strchr("Hello world", '\0'));
}*/
