/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:13:06 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/22 17:29:21 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	manage_print_string(va_list *args)
{
	char	*s;

	s = va_arg(*args, char *);
	if (s == 0)
		return (ft_printf("(null)", 1));
	return (ft_putstr_fd(s, 1));
}
