/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:10:30 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 19:02:45 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	char			*tmp;
	unsigned char	ch;

	tmp = (char *) s;
	ch = (unsigned char) c;
	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	if (ch == '\0')
	{
		return (&tmp[len]);
	}
	while (len >= 0)
	{
		if (s[len] == ch)
			return (&tmp[len]);
		len--;
	}
	tmp = 0;
	return (tmp);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "Hello world";

	printf("%s", ft_strrchr(str, 'x'));
}*/
