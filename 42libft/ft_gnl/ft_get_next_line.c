/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:26 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/09 14:14:07 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

unsigned long long	is_line_feed(t_str *str)
{
	unsigned long long	i;
	t_char_list			*buffer;

	if (!str || !str->head)
		return (0);
	buffer = str->head;
	i = str->start;
	while (i < str->size + str->start)
	{
		if (i != 0 && i % T_STR_BUFFER_SIZE == 0)
		{
			buffer = buffer->next;
			if (!buffer)
				return (0);
		}
		if (buffer->c[i % T_STR_BUFFER_SIZE] == '\n')
			return (i - str->start + 1);
		i++;
	}
	return (0);
}

static int	is_buffer_line_feed(char *str, ssize_t len)
{
	ssize_t	i;

	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	populate_line(t_str *s, int fd)
{
	char	*buffer;
	ssize_t	byte_readed;

	if (!s)
		return (-2);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return (-2);
	byte_readed = read(fd, buffer, BUFFER_SIZE);
	while (byte_readed > 0)
	{
		if (!ft_str_push(s, buffer, byte_readed))
		{
			free(buffer);
			return (-2);
		}
		if (is_buffer_line_feed(buffer, byte_readed))
		{
			free(buffer);
			return (-3);
		}
		byte_readed = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (byte_readed);
}

static unsigned long long	get_line_size(t_str *str, int fd)
{
	int					read_status;
	unsigned long long	line_size;

	if (!str)
		return (0);
	line_size = is_line_feed(str);
	if (!line_size)
	{
		read_status = populate_line(str, fd);
		if (read_status == -2 || read_status == -1)
			return (0);
		if (read_status == -3)
			line_size = is_line_feed(str);
		else
			line_size = str->size;
	}
	return (line_size);
}

char	*get_next_line(int fd)
{
	static t_str		*str[1024];
	unsigned long long	line_size;
	char				*line;

	if (fd < 0)
		return (ft_str_free(str[~fd]), str[~fd] = 0, (char *)0);
	if (fd < 0 || fd >= 1024)
		return (0);
	if (!str[fd])
		str[fd] = ft_str_create();
	if (!str[fd])
		return (0);
	line_size = get_line_size(str[fd], fd);
	if (!line_size)
	{
		ft_str_free(str[fd]);
		str[fd] = 0;
		return (0);
	}
	line = ft_str_get_char_array(str[fd], line_size);
	if (!line)
		return (0);
	ft_str_troncate_begin(str[fd], line_size);
	return (line);
}
