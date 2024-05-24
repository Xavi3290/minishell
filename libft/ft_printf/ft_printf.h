/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:52:53 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/24 15:20:08 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_flags
{
	int		fill_zero;
	int		left_justify;
	int		sign;
	int		space;
	int		truncate;
	int		format;
	int		width;
	char	command;
}	t_flags;

int		ft_printf(const char *s, ...);
char	*ft_read_string(char *s);
char	*ft_read_ptr(uintptr_t num, char *base);
char	*ft_utoa(unsigned int n);
char	*ft_uitobase(unsigned int num, char *base);
int		ft_print_str(char *s, int fd);
int		ft_check_flags(const char **s, va_list args);
int		print_x_char(int qty, unsigned int c);
int		print_ptr_flags(uintptr_t ptr, t_flags *flags);
int		print_str_width(char *s, t_flags *flags, int flags_len);
int		print_char_flags(unsigned int c, t_flags *flags);
int		print_ptr_flags(uintptr_t ptr, t_flags *flags);
int		print_str_flags(char *s, t_flags *flags);
int		print_int_flags(long num, t_flags *flags);
int		print_int_justify(long num, t_flags *flags, int sign);
int		print_int_sign(int num, t_flags *flags);
int		print_int_truncate(long num, t_flags *flags, int sign);
int		print_int_zero(long num, t_flags *flags, int sign);
int		print_int_width(long num, t_flags *flags, int sign);
int		print_hexa_flags(unsigned long num, t_flags *flags, int caps);
int		print_hexa_truncate(char *s, t_flags *flags, int caps);
int		print_hexa_format(int caps);
int		print_hexa_zero(char *s, t_flags *flags, int caps);
int		print_hexa_width(char *s, t_flags *flags, int caps);
int		print_hexa_justify(char *s, t_flags *flags, int caps);
int		print_hexa_format_str(char *s, int caps);
int		print_num_zero(t_flags *flags);
char	*transform_number(long num);
int		free_and_out(char *s);

#endif
