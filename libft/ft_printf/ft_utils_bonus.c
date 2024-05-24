/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:05:41 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/01 16:53:09 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//Printa X veces el caracter. Retorna length o -1 si write falla
int	print_x_char(int qty, unsigned int c)
{
	int	len;

	len = 0;
	while (qty-- > 0)
	{
		if (ft_putchar_fd(c, 1) == -1)
			return (-1);
		len++;
	}
	return (len);
}

//Printa espacios dependiendo de la flag '-'. Retorna length o -1 si falla.
int	print_str_width(char *s, t_flags *flags, int flags_len)
{
	int	len;

	len = ft_strlen(s);
	len += flags_len;
	if (flags->left_justify)
	{
		if (ft_print_str(s, 1) == -1)
			return (-1);
		if (print_x_char(flags->width - len, ' ') == -1)
			return (-1);
		return (len + (flags->width - len));
	}
	else
	{
		if (print_x_char(flags->width - len, ' ') == -1)
			return (free_and_out(s));
		if (ft_print_str(s, 1) == -1)
			return (-1);
		return (len + (flags->width - len));
	}
}

//Funcion que transforma un long en char*
char	*transform_number(long num)
{
	char	*s;

	if (num > 2147483647)
		s = ft_utoa(num);
	else
		s = ft_itoa(num);
	if (!s)
		return (NULL);
	return (s);
}

//Funcion que gestiona el valor 0 con flag '.'
int	print_num_zero(t_flags *flags)
{
	if (flags->left_justify && flags->sign && flags->width > 1)
	{
		if (print_int_sign(0, flags) == -1
			|| print_x_char(flags->width -1, ' ') == -1)
			return (-1);
		return (flags->width);
	}
	if (flags->width + flags->sign + flags->space == 0)
		return (0);
	else if (flags->width <= 1 && flags->space)
		return (ft_putchar_fd(' ', 1));
	else
	{
		if (print_x_char(flags->width - flags->sign - flags->space, ' ') == -1)
			return (-1);
		if (print_int_sign(0, flags) == -1)
			return (-1);
	}
	if (!flags->width)
		return (flags->sign);
	return (flags->width);
}

//Funcion que printa "0x" o "0X" delante de la cadena hexadecimal
int	print_hexa_format_str(char *s, int caps)
{
	int	len;

	len = ft_strlen(s);
	if (print_hexa_format(caps) == -1)
		return (free_and_out(s));
	if (ft_print_str(s, 1) == -1)
		return (-1);
	return (2 + len);
}
