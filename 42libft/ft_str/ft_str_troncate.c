/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_troncate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:41 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/07 07:49:01 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_str_troncate_begin(t_str *str, unsigned long long size)
{
	t_char_list	*buffer;

	if (!str)
		return (0);
	if (size >= str->size)
		size = str->size;
	str->size -= size;
	str->start += size;
	while (str->start >= T_STR_BUFFER_SIZE)
	{
		if (!str->head)
			return (0);
		buffer = str->head;
		str->head = str->head->next;
		free(buffer);
		str->start -= T_STR_BUFFER_SIZE;
	}
	return (1);
}
