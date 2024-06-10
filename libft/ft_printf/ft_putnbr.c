/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:53:19 by cgaratej          #+#    #+#             */
/*   Updated: 2024/04/10 11:54:16 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_num_min(void)
{
	if (ft_putstr("-2147483648") == -1)
		return (-1);
	return (ft_strlen_pf("-2147483648"));
}

int	ft_putnbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (ft_num_min());
	if (n < 0 && ++len)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		n = -n;
	}
	if (n > 9)
	{
		len += ft_putnbr(n / 10);
		if (len == -1)
			return (-1);
		n = n % 10;
	}
	if (n <= 9)
	{
		if (ft_putchar(('0' + n)) == -1)
			return (-1);
		len++;
	}
	return (len);
}
