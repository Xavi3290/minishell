/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_flags_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:17:16 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/02 17:37:36 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//Funcion que gestiona %x y %X con flag '.'. Retorna length
int	print_hexa_truncate(char *s, t_flags *flags, int caps)
{
	int	len;

	len = ft_strlen(s);
	if (flags->format)
		len += 2;
	if (flags->truncate - (int)ft_strlen(s) > 0)
		len += flags->truncate - (int)ft_strlen(s);
	while (len < flags->width)
	{
		if (ft_putchar_fd(' ', 1) == -1)
			return (free_and_out(s));
		len++;
	}
	if (flags->format)
	{
		if (print_hexa_format(caps) == -1)
			return (free_and_out(s));
	}
	if (print_x_char(flags->truncate - (int)ft_strlen(s), '0') == -1)
		return (free_and_out(s));
	if (ft_print_str(s, 1) == -1)
		return (-1);
	return (len);
}

//Funcion que gestiona %x y %X con flag '#'. Retorna length
int	print_hexa_format(int caps)
{
	if (caps)
	{
		if (ft_putchar_fd('0', 1) == -1 || ft_putchar_fd('X', 1) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar_fd('0', 1) == -1 || ft_putchar_fd('x', 1) == -1)
			return (-1);
	}
	return (2);
}

//Funcion que gestiona %x y %X con flag '0'. Retorna length
int	print_hexa_zero(char *s, t_flags *flags, int caps)
{
	int	len;

	len = ft_strlen(s);
	if (flags->format)
	{
		if (print_hexa_format(caps) == -1)
			return (free_and_out(s));
		len += 2;
	}
	if (print_x_char(flags->width - len, '0') == -1)
		return (free_and_out(s));
	if (ft_print_str(s, 1) == -1)
		return (-1);
	if (flags->width - len > 0)
		return (flags->width);
	return (len);
}

//Funcion que gestiona %x y %X con flag '-'. Retorna length
int	print_hexa_justify(char *s, t_flags *flags, int caps)
{
	int	len;

	len = ft_strlen(s);
	if (flags->format)
	{
		if (print_hexa_format(caps) == -1)
			return (free_and_out(s));
		len += 2;
	}
	if (flags->truncate > (int)ft_strlen(s))
	{
		if (print_x_char(flags->truncate - ft_strlen(s), '0') == -1)
			return (free_and_out(s));
		len += (flags->truncate - (int)ft_strlen(s));
	}
	if (ft_print_str(s, 1) == -1)
		return (-1);
	if (flags->width - len > 0)
	{
		if (print_x_char(flags->width - len, ' ') == -1)
			return (-1);
		len += (flags->width - len);
	}
	return (len);
}

//Funcion que gestiona %x y %X con flag "width". Retorna length
int	print_hexa_width(char *s, t_flags *flags, int caps)
{
	int	len;

	len = ft_strlen(s);
	if (flags->format)
		len += 2;
	if (print_x_char(flags->width - len, ' ') == -1)
		return (free_and_out(s));
	if (flags->format)
	{
		if (print_hexa_format(caps) == -1)
			return (free_and_out(s));
	}
	if (ft_print_str(s, 1) == -1)
		return (-1);
	if (flags->width - len > 0)
		return (flags->width);
	return (len);
}
