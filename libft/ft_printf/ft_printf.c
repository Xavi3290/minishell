/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:47:48 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/30 17:27:37 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//Comprueba tipo de dato y llama funcion encargada. Retorna length
int	ft_check_args(const char *s, va_list args)
{
	char	*content;

	content = NULL;
	if (*s == 's')
		content = ft_read_string(va_arg(args, char *));
	else if (*s == 'c')
		return (ft_putchar_fd(va_arg(args, unsigned int), 1));
	else if (*s == 'p')
		content = ft_read_ptr((uintptr_t) va_arg(args, void *),
				"0123456789abcdef");
	else if (*s == 'd')
		content = ft_itoa(va_arg(args, int));
	else if (*s == 'i')
		content = ft_itoa(va_arg(args, int));
	else if (*s == 'u')
		content = ft_utoa(va_arg(args, unsigned int));
	else if (*s == 'x')
		content = ft_uitobase(va_arg(args, unsigned int), "0123456789abcdef");
	else if (*s == 'X')
		content = ft_uitobase(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (*s == '%')
		return (ft_putchar_fd('%', 1));
	return (ft_print_str(content, 1));
}

//Funcion principal
int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			total;
	int			sum;

	va_start(args, s);
	if (!s || !*s)
		return (0);
	total = 0;
	while (*s != '\0')
	{
		if (*s == '%' && (ft_strchr("cspdiuxX%", *(s + 1))))
			sum = ft_check_args(++s, args);
		else if (*s == '%')
			sum = ft_check_flags(&s, args);
		else
			sum = write(1, s, 1);
		if (sum == -1)
			return (-1);
		s++;
		total += sum;
	}
	va_end(args);
	return (total);
}

/*
int	main(void)
{
	
	char	s[] = " que tal ";
	int		d[] = {1, 2};
	
	
	printf("Length: %d\n", ft_printf("hola%+05smundo %c %p %d, %i %u %x %X %%",
		"", '-', 0, 27292873, -2147483647, -2147483646, 0, 0));

	printf("\n01234567890123456789012345678901234567890\n\n");

	printf("Lenght: %d\n", printf("hola%smundo %c %p %d, %i %u %x %X %%",
		"", '-', 0, 27292873, -2147483647, -2147483646, 0, 0));

	printf("Lenght: %d\n", ft_printf(" NULL %s NULL ", NULL));
	printf("Lenght: %d\n", printf(" NULL %s NULL ", NULL));

	printf("Lenght: %d\n", ft_printf(" %c %c %c ", '2', '1', 0));
	printf("Lenght: %d\n", printf(" %c %c %c ", '2', '1', 0));

	printf("Lenght: %d\n", ft_printf("%%"));
	printf("Lenght: %d\n", printf("%%"));


	//FLAGS
	
	//printf("Lenght: %d\n", printf("%7chola", 'g'));
	//printf("Lenght: %d\n", ft_printf("%7chola", 'g'));
	printf("Lenght: %d\n", printf("%-20phola%-7cque%-9%tal%-s",
		"hola que tal", 'y', "-"));
	printf("Lenght: %d\n", ft_printf("%-20phola%-7cque%-9%tal%-s",
		"hola que tal", 'y', "-"))
}*/
