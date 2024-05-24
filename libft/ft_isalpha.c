/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:10:46 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/12 20:35:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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
	printf("%d: %s\n", ft_isalpha('H'), "H");
	printf("%d: %s\n", ft_isalpha('4'), "4");
	printf("%d: %s\n", ft_isalpha('*'), "*");
}*/
