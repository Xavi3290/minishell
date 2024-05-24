/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:05:25 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 18:55:41 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static int	count_char(int n)
{
	int	dig;

	dig = 0;
	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	else if (n < 0)
	{
		dig++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		dig++;
	}
	return (dig);
}

static int	pow_ten(int dig)
{
	int	res;

	res = 1;
	while (dig > 1)
	{
		res *= 10;
		dig--;
	}
	return (res);
}

static char	*put_string(int n, char *res, int dig)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if (n < 0)
	{
		res[i++] = '-';
		dig--;
		num = ((n / pow_ten(dig)) * -1) + '0';
		res[i++] = num;
		n += ((n / pow_ten(dig)) * pow_ten(dig)) * -1;
		dig--;
		n *= -1;
	}
	while (dig > 0)
	{
		res[i++] = (n / pow_ten(dig)) + '0';
		n -= (n / pow_ten(dig)) * pow_ten(dig);
		dig--;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		dig;

	if (n == 0)
	{
		res = (char *) malloc(2 * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	else
	{
		dig = count_char(n);
		res = (char *) malloc((dig + 1) * sizeof(char));
		if (!res)
			return (NULL);
		return (put_string(n, res, dig));
	}
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s", ft_itoa(0));
}*/
