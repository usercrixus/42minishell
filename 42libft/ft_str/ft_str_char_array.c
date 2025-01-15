/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_char_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:15:35 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 04:34:05 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_str_get_char_array(t_str *str, unsigned long long line_size)
{
	char				*line;
	t_char_list			*buffer;
	unsigned long long	i;

	if (line_size <= 0 || !str)
		return (ft_strdup(""));
	line = (char *)malloc(sizeof(char) * (line_size + 1));
	if (!line)
		return (0);
	buffer = str->head;
	i = 0;
	while (i < line_size)
	{
		if (!buffer)
		{
			free(line);
			return (0);
		}
		line[i] = (buffer->c)[(i + str->start) % T_STR_BUFFER_SIZE];
		i++;
		if ((i + str->start) % T_STR_BUFFER_SIZE == 0)
			buffer = buffer->next;
	}
	line[i] = '\0';
	return (line);
}
