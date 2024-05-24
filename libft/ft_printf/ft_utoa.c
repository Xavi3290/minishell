/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:21:00 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/30 16:22:51 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//Cuenta digitos de un entero sin signo
static int	count_char(unsigned int n)
{
	int	dig;

	dig = 0;
	while (n > 0)
	{
		n /= 10;
		dig++;
	}
	return (dig);
}

//Devuelve potencias de 10 en base a los digitos
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

//Transforma unsigned int en char* y devuelve el valor.
static char	*put_string(unsigned int n, char *res, int dig)
{
	int	i;

	i = 0;
	while (dig > 0)
	{
		res[i++] = (n / pow_ten(dig)) + '0';
		n -= (n / pow_ten(dig)) * pow_ten(dig);
		dig--;
	}
	res[i] = '\0';
	return (res);
}

//Funcion que recibe un unsigned int y la transforma en char*
char	*ft_utoa(unsigned int n)
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
	printf("%s", ft_utoa(-2147483647));
}*/
