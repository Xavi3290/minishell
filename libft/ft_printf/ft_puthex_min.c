/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:41:32 by cgaratej          #+#    #+#             */
/*   Updated: 2024/04/10 11:57:09 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_long(char *base, long n, int len)
{
	unsigned long	b;

	b = ft_strlen_pf(base);
	if (n >= b)
	{
		len = ft_hex_long(base, n / b, len);
		if (len == -1)
			return (-1);
		if (write (1, &base[n % b], 1) == -1)
			return (-1);
		len++;
	}
	else if (n < b)
	{
		if (write (1, &base[n % b], 1) == -1)
			return (-1);
		len++;
	}
	return (len);
}

static int	ft_hex_uns(char *base, unsigned int n, int len)
{
	unsigned int	b;

	b = ft_strlen_pf(base);
	if (n >= b)
	{
		len = ft_hex_uns(base, n / b, len);
		if (len == -1)
			return (-1);
		if (write (1, &base[n % b], 1) == -1)
			return (-1);
		len++;
	}
	else if (n < b)
	{
		if (write (1, &base[n % b], 1) == -1)
			return (-1);
		len++;
	}
	return (len);
}

int	ft_puthex_min(int n, char type)
{
	int	len;

	len = 0;
	if (type == 'x')
	{
		if (n >= 0)
			len = ft_hex_long("0123456789abcdef", n, len);
		else if (n < 0)
			len = ft_hex_uns("0123456789abcdef", n, len);
	}
	else if (type == 'X')
	{
		if (n >= 0)
			len = ft_hex_long("0123456789ABCDEF", n, len);
		else if (n < 0)
			len = ft_hex_uns("0123456789ABCDEF", n, len);
	}
	if (len == -1)
		return (-1);
	return (len);
}
