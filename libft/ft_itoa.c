/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:13:58 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/30 14:57:11 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getint_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_fill_str(char *str, int n, int len)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		i = 1;
	}
	if (n == 0)
		str[i] = '0';
	str[len] = '\0';
	len--;
	while (n)
	{
		str[len] = n % 10 + '0';
		len--;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_getint_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (0);
	ft_fill_str(str, n, len);
	return (str);
}

/*#include <stdio.h>

int main(void)
{
	char *h = ft_itoa(55);

	printf("%s\n", h);
	return (0);
}*/