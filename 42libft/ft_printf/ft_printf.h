/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 02:07:44 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/11 03:40:55 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./../ft_base/libft.h"
# include <stdarg.h>

int	manage_print_hex(va_list *args);
int	manage_print_hex_uppercase(va_list *args);
int	manage_print_pointer(va_list *args);
int	manage_print_decimal(va_list *args);
int	manage_unsigned_decimal(va_list *args);
int	manage_print_char(va_list *args);
int	manage_print_string(va_list *args);
int	ft_printf(const char *format, ...);

#endif
