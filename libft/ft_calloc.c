/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:39:32 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 12:24:28 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*#include <stdio.h>

int main(void) 
{
    size_t num_elements = 5;
    size_t element_size = sizeof(int);

    int *arr = (int *)ft_calloc(num_elements, element_size);

    if (arr != NULL) {
        for (size_t i = 0; i < num_elements; i++) {
            printf("arr[%zu] = %d\n", i, arr[i]);
        }
        free(arr);
    } else {
        printf("Error al asignar memoria.\n");
    }
    return (0);
}*/