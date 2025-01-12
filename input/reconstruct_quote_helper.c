/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:53:40 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 03:37:44 by achaisne         ###   ########.fr       */
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

int	set_command(char **commands, t_str **buffer, int i)
{
	if (!(*buffer))
	{
		shift(&commands[i], 1);
		return (*buffer = 0, 1);
	}
	free(commands[i]);
	commands[i] = ft_str_get_char_array(*buffer, (*buffer)->size);
	if (!commands[i])
		return (ft_str_free(*buffer), 0);
	ft_str_free(*buffer);
	return (*buffer = 0, 1);
}

int	get_char_occurence(char *str, char c)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			result++;
		i++;
	}
	return (result);
}
