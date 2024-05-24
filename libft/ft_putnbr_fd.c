/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:53:36 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/12 21:35:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pow_ten(int exp)
{
	int	res;

	res = 1;
	while (exp-- > 0)
		res *= 10;
	return (res);
}

static void	write_nb(int n, int fd)
{
	int		dig;
	int		n_cpy;
	char	c;

	n_cpy = n;
	dig = 0;
	while (n_cpy > 0)
	{
		n_cpy /= 10;
		dig++;
	}
	while (dig > 0)
	{
		c = (n / pow_ten(dig - 1)) + '0';
		n -= (n / pow_ten(dig - 1)) * pow_ten(dig - 1);
		dig--;
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
		write_nb(n, fd);
	}
	else
		write_nb(n, fd);
}

/*
int	main(void)
{
	ft_putnbr_fd(-273820, 1);
}*/
