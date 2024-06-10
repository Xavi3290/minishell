/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:48:28 by cgaratej          #+#    #+#             */
/*   Updated: 2024/04/10 11:54:35 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex(char *base, unsigned long n, int len)
{
	unsigned long	b;

	b = ft_strlen_pf(base);
	if (n >= b)
	{
		len = ft_hex(base, n / b, len);
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

int	ft_putmem(void *p)
{
	unsigned long	punt;
	int				len;

	len = 0;
	punt = (unsigned long)p;
	if (write(1, "0x", 2) != 2)
		return (-1);
	len = ft_hex("0123456789abcdef", punt, len);
	if (len == -1)
		return (-1);
	len += 2;
	return (len);
}
