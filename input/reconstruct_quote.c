/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:37:10 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 09:32:28 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	manage_reconstruct_quote(char **commands)
{
	int		i;
	int		j;
	t_str	*buffer;
	char	quote;

	buffer = 0;
	quote = 0;
	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			if (set_quote(&quote, &commands[i][j]))
			{
				if (!initialize_buffer(&buffer))
					return (0);
				j++;
			}
			else if (!push_char(&buffer, &commands[i][j++]))
				return (0);
		}
		if (!set_command_arg(commands, buffer, i++))
			return (0);
		buffer = 0;
	}
	return (1);
}

int	reconstruct_quote(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (!manage_reconstruct_quote(commands[i]))
			return (0);
		if (!commands[i][0])
		{
			commands[i][0] = ft_strdup("true");
			if (!commands[i][0])
				return (0);
		}
		i++;
	}
	return (1);
}
