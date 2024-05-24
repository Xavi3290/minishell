/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:22 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/12 20:39:08 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
	printf("%d: %s\n", ft_isascii('H'), "H");
	printf("%d: %s\n", ft_isascii('4'), "4");
	printf("%d: %s\n", ft_isascii('*'), "*");
}*/
