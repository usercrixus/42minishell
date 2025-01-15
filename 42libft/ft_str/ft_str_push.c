/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:41 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/02 15:41:23 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static int	ft_str_push_node(t_str *str)
{
	t_char_list	*node;

	if (!str)
		return (0);
	node = (t_char_list *)malloc(sizeof(t_char_list) * 1);
	if (!node)
		return (0);
	node->next = 0;
	if (str->head == 0)
		str->head = node;
	else
		str->tail->next = node;
	str->tail = node;
	return (1);
}

int	ft_str_push(t_str *str, char *c, ssize_t len)
{
	ssize_t	i;

	if (!str || !c)
		return (0);
	i = 0;
	while (i < len)
	{
		if ((str->size + str->start + i) % T_STR_BUFFER_SIZE == 0)
			if (!ft_str_push_node(str))
				return (0);
		(str->tail->c)[(str->size + str->start + i) % T_STR_BUFFER_SIZE] = c[i];
		i++;
	}
	str->size += len;
	return (1);
}
