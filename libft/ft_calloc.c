/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:56:46 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/15 19:32:54 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*res;

	res = malloc(nelem * elsize);
	if (res == NULL)
		return (res);
	else
		ft_bzero(res, nelem * elsize);
	return (res);
}

/*
int	main(void)
{
	char	*ptr;
	char	*ptr2;

	ptr = (char *)calloc(5, sizeof(char));
	ptr2 = (char *)ft_calloc(5, sizeof(char));
}*/
