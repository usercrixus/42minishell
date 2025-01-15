/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:11:02 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/11 04:27:01 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_udecimal(unsigned int i)
{
	if (i > 9)
		return (print_udecimal(i / 10) + ft_putchar_fd(i % 10 + '0', 1));
	else
		return (ft_putchar_fd(i % 10 + '0', 1));
}

int	manage_print_decimal(va_list *args)
{
	int	i;

	i = va_arg(*args, int);
	return (ft_putnbr_fd(i, 1));
}

int	manage_unsigned_decimal(va_list *args)
{
	unsigned int	i;

	i = va_arg(*args, unsigned int);
	return (print_udecimal(i));
}
