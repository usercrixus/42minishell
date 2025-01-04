/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:53:40 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/04 20:58:45 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_quote(char *quote, int *j)
{
	*quote = 0;
	(*j)++;
}

void	set_quote(char *quote, int *j, char c)
{
	*quote = c;
	(*j)++;
}

int	set_command(char **commands, t_str *buffer, int i)
{
	free(commands[i]);
	commands[i] = ft_str_get_char_array(buffer, buffer->size);
	if (!commands[i])
		return (ft_str_free(buffer), 0);
	ft_str_free(buffer);
	return (1);
}
