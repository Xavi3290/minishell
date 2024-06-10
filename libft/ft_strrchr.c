/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:42:57 by cgaratej          #+#    #+#             */
/*   Updated: 2024/01/29 11:52:52 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*ch;

	ch = (char *)s;
	len = ft_strlen(ch) + 1;
	while (len > 0)
	{
		if (ch[len - 1] == (char)c)
			return (&ch[len - 1]);
		len--;
	}
	return (0);
}

/*#include <stdio.h>

int main() {
    const char *str = "";
    int target_char = '\0';

    char *result = strrchr(str, target_char);

    if (result != NULL) {
        printf("%d.\n", target_char);
    } else {
        printf("Carácter '%c' no encontrado en la cadena.\n", target_char);
    }

    return (0);
}*/