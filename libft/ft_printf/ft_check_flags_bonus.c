/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:13:57 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/31 22:35:05 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//Reserva memoria, inicializa y retorna t_flags
t_flags	*initialize_flags(void)
{
	t_flags	*flags;

	flags = malloc(sizeof(t_flags));
	if (!flags)
		return (NULL);
	flags->left_justify = 0;
	flags->fill_zero = 0;
	flags->sign = 0;
	flags->space = 0;
	flags->truncate = -1;
	flags->format = 0;
	flags->width = 0;
	return (flags);
}

//LLama funcion encargada de printar con flags segun comando. Retorna length
int	function_call(va_list args, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->command == 'c')
		len = print_char_flags(va_arg(args, unsigned int), flags);
	else if (flags->command == 'p')
		len = print_ptr_flags((uintptr_t) va_arg(args, void *), flags);
	else if (flags->command == 's')
		len = print_str_flags(va_arg(args, char *), flags);
	else if (flags->command == 'd')
		len = print_int_flags(va_arg(args, int), flags);
	else if (flags->command == 'i')
		len = print_int_flags(va_arg(args, int), flags);
	else if (flags->command == 'u')
		len = print_int_flags(va_arg(args, unsigned int), flags);
	else if (flags->command == 'x')
		len = print_hexa_flags(va_arg(args, unsigned long), flags, 0);
	else if (flags->command == 'X')
		len = print_hexa_flags(va_arg(args, unsigned long), flags, 1);
	else if (flags->command == '%')
		len = print_char_flags('%', flags);
	free(flags);
	return (len);
}

//Funcion que gestiona ciertas flags y las anade a la struct
void	flags_one(const char **s, t_flags *flags)
{
	if (**s == '-')
		flags->left_justify = 1;
	else if (**s == '+')
		flags->sign = 1;
	else if (**s == ' ')
		flags->space = 1;
	else if (**s == '#')
		flags->format = 1;
}

//Funcion que gestiona el resto de flags y las anade a la struct
void	flags_two(const char **s, t_flags *flags)
{
	if (**s == '0')
		flags->fill_zero = 1;
	else if (ft_isdigit(**s))
	{
		flags->width = ft_atoi(*s);
		while (ft_isdigit(*(*s + 1)))
			(*s)++;
	}
	else if (**s == '.')
	{
		flags->truncate = ft_atoi(*s + 1);
		while (ft_isdigit(*(*s + 1)))
			(*s)++;
	}
}

//Lee flags y llama a funcion necesaria para gestionarlas. Retorna length
int	ft_check_flags(const char **s, va_list args)
{
	t_flags	*flags;

	flags = initialize_flags();
	if (!flags)
		return (-1);
	(*s)++;
	while (!ft_strchr("cpsdiuxX%", **s))
	{
		if (**s == '-' || **s == '+' || **s == ' ' || **s == '#')
			flags_one(s, flags);
		else if (**s == '0' || **s == '.' || ft_isdigit(**s))
			flags_two(s, flags);
		(*s)++;
	}
	flags->command = **s;
	return (function_call(args, flags));
}
