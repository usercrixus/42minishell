/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:07:15 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/02 14:05:53 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_rooting(char c, va_list *args)
{
	if (c == 'c')
		return (manage_print_char(args));
	else if (c == 's')
		return (manage_print_string(args));
	else if (c == 'p')
		return (manage_print_pointer(args));
	else if (c == 'd')
		return (manage_print_decimal(args));
	else if (c == 'i')
		return (manage_print_decimal(args));
	else if (c == 'u')
		return (manage_unsigned_decimal(args));
	else if (c == 'x')
		return (manage_print_hex(args));
	else if (c == 'X')
		return (manage_print_hex_uppercase(args));
	else if (c == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		print_size;

	if (!format)
		return (-1);
	va_start(args, format);
	print_size = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			print_size += print_rooting(format[i + 1], &args);
			i += 2;
		}
		else
		{
			print_size += ft_putchar_fd(format[i], 1);
			i++;
		}
	}
	va_end(args);
	return (print_size);
}
