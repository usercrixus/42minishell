/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:41 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 08:25:10 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

void	ft_str_free(t_str *str)
{
	t_char_list	*buffer;

	while (str->head)
	{
		buffer = str->head;
		str->head = str->head->next;
		free(buffer);
	}
	free(str);
}

t_str	*ft_str_create(void)
{
	t_str	*str;

	str = (t_str *)malloc(sizeof(t_str) * 1);
	if (!str)
		return (0);
	str->head = 0;
	str->tail = 0;
	str->size = 0;
	str->start = 0;
	return (str);
}
