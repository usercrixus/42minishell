/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:37:10 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 21:11:01 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	manage_reconstruct_quote_arg(char *commands, t_str **buffer)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (commands[i])
	{
		if (set_quote(&quote, &commands[i]))
		{
			if (!initialize_buffer(buffer))
				return (0);
		}
		else if (!push_char(buffer, &commands[i]))
			return (0);
		i++;
	}
	return (1);
}

int	manage_reconstruct_quote_cmd(char **commands)
{
	t_str	*buffer;
	int		i;

	buffer = 0;
	i = 0;
	while (commands[i])
	{
		manage_reconstruct_quote_arg(commands[i], &buffer);
		if (!set_command_arg(commands, buffer, i))
			return (0);
		i++;
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
		if (!manage_reconstruct_quote_cmd(commands[i]))
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
