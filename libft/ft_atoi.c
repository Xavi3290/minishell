/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:34:24 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/26 13:25:40 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	simbol;
	int	result;
	int	i;

	result = 0;
	simbol = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] && (nptr[i] == 43 || nptr[i] == 45))
	{
		if (nptr[i] == 45)
			simbol *= -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = ((result * 10) + (nptr[i] - '0'));
		i++;
	}
	result *= simbol;
	return (result);
}

/*#include <stdio.h>

int	main(void)
{
	int num0 = ft_atoi("	 		  -557");
	int num1 = ft_atoi("	 		  -557sdfasdf");
	int num2 = ft_atoi("	 		  ---557sdfasdf");
	int num3 = ft_atoi("	 		  +557sdfasdf");
	int num4 = ft_atoi("	 		  +-9557sdfasdf");

	printf("%d\n", num0);
	printf("%d\n", num1);
	printf("%d\n", num2);
	printf("%d\n", num3);
	printf("%d\n", num4);
	return (0);
}*/
