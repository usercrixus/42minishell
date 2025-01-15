/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:09:09 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/22 15:57:37 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hex(unsigned long l)
{
	const char	*hex_digits = "0123456789abcdef";

	if (l > 15)
		return (print_hex(l / 16) + ft_putchar_fd(hex_digits[l % 16], 1));
	else
		return (ft_putchar_fd(hex_digits[l % 16], 1));
}

static int	print_hex_upper(unsigned long l)
{
	const char	*hex_digits = "0123456789ABCDEF";

	if (l > 15)
		return (print_hex_upper(l / 16) + ft_putchar_fd(hex_digits[l % 16], 1));
	else
		return (ft_putchar_fd(hex_digits[l % 16], 1));
}

int	manage_print_hex(va_list *args)
{
	unsigned int	i;

	i = va_arg(*args, unsigned int);
	return (print_hex(i));
}

int	manage_print_hex_uppercase(va_list *args)
{
	unsigned int	i;

	i = va_arg(*args, unsigned int);
	return (print_hex_upper(i));
}

int	manage_print_pointer(va_list *args)
{
	void	*p;

	p = va_arg(*args, void *);
	if (p == 0)
		return (ft_putstr_fd("(nil)", 1));
	return (ft_putstr_fd("0x", 1) + print_hex((unsigned long)p));
}
