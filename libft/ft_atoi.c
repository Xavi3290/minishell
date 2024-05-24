/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:35 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/12 18:56:06 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	pow_ten(int exp)
{
	int	res;

	res = 1;
	while (exp-- > 0)
		res *= 10;
	return (res);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (str[i] >= 48 && str[i] <= 57)
		i++;
	while (*str >= 48 && *str <= 57)
	{
		res += (*str - '0') * pow_ten(i-- - 1);
		str++;
	}
	return (res * sign);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("%d\n", ft_atoi("-2147483650"));
	printf("%d\n", atoi("-2147483650"));
}*/
