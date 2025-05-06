/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 07:37:24 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/15 14:43:07 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	initialize_buffer(t_str **buffer)
{
	if (!*buffer)
	{
		*buffer = ft_str_create();
		if (!*buffer)
			return (0);
	}
	return (1);
}

int	push_char(t_str **buffer, char *command)
{
	if (!initialize_buffer(buffer))
		return (0);
	if (!ft_str_push(*buffer, command, 1))
		return (ft_str_free(*buffer), 0);
	return (1);
}

int	set_quote(char *quote, char *s)
{
	if (!*quote && (*s == '\'' || *s == '"') && gco(s, *s) > 1)
	{
		*quote = *s;
		return (1);
	}
	else if (*s == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	set_command_arg(char **commands, t_str *buffer, int i)
{
	if (!(buffer))
	{
		shift(&commands[i], 1);
		return (1);
	}
	free(commands[i]);
	commands[i] = ft_str_get_char_array(buffer, buffer->size);
	if (!commands[i])
		return (ft_str_free(buffer), 0);
	ft_str_free(buffer);
	return (1);
}
