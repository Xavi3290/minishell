/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:08:36 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/01 16:23:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//Transforma unsigned int en char*
char	*ft_uitobase(unsigned int num, char *base)
{
	int				len;
	unsigned int	n;
	char			*res;

	if (num == 0)
		return (ft_strdup("0"));
	n = num;
	len = 0;
	while (n != 0)
	{
		len++;
		n = n / ft_strlen(base);
	}
	res = (char *) malloc ((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	while (num != 0)
	{
		res[len--] = base[num % ft_strlen(base)];
		num /= ft_strlen(base);
	}
	return (res);
}

//Crea un char* con el valor de s o crea uno con "(null)" si s == null
char	*ft_read_string(char *s)
{
	char	*content;

	content = NULL;
	if (!s)
		content = ft_strdup("(null)");
	else
		content = ft_strdup(s);
	if (!content)
		return (NULL);
	return (content);
}

//Printa una string y devuelve length. -1 si write falla 
int	ft_print_str(char *s, int fd)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_putchar_fd(s[i], fd) == -1)
			return (free_and_out(s));
		i++;
	}
	free(s);
	return (i);
}

//Devuelve length esperada al transformar una direccion de memoria a hexadecimal
static int	ptr_length(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

//Transforma una direccion de memoria en formato numerico a char* en hexadecimal
char	*ft_read_ptr(uintptr_t num, char *base)
{
	int			len;
	char		*res;
	uintptr_t	x;

	if (!num)
		return (ft_strdup("0x0"));
	x = num;
	len = ptr_length(num) + 2;
	res = (char *) malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	while (x != 0)
	{
		res[len--] = base[x % 16];
		x /= 16;
	}
	res[1] = 'x';
	res[0] = '0';
	return (res);
}
