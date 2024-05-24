/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:09:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/12 20:34:15 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d: %s\n", ft_isalnum('H'), "H");
	printf("%d: %s\n", ft_isalnum('4'), "4");
	printf("%d: %s\n", ft_isalnum('*'), "*");
}*/
