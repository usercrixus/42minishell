/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 05:43:07 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 05:45:08 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_reconstruct_quote(char *quote, char c)
{
	if (!*quote)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
	return (1);
}

void	set_value(char quote, char *commands_string, char **value)
{
	if (!quote && ft_strncmp(commands_string, "<<", 2) == 0)
		*value = " << ";
	else if (!quote && ft_strncmp(commands_string, "<", 1) == 0)
		*value = " < ";
	else if (!quote && ft_strncmp(commands_string, ">>", 2) == 0)
		*value = " >> ";
	else if (!quote && ft_strncmp(commands_string, ">", 1) == 0)
		*value = " > ";
	else
		*value = 0;
}

int	reconstruct_space_helper(char **commands_string, int i, t_str *buffer)
{
	int		j;
	char	quote;
	char	*value;

	quote = 0;
	j = 0;
	while (commands_string[i][j])
	{
		if (commands_string[i][j] == '\'' || commands_string[i][j] == '"')
			set_reconstruct_quote(&quote, commands_string[i][j]);
		else
		{
			set_value(quote, &commands_string[i][j], &value);
			if (value)
			{
				if (!ft_str_push(buffer, value, ft_strlen(value)))
					return (0);
				j += ft_strlen(value) - 2;
				continue ;
			}
		}
		if (!ft_str_push(buffer, &commands_string[i][j++], 1))
			return (0);
	}
	return (1);
}

int	reconstruct_space(char **commands_string)
{
	int		i;
	t_str	*buffer;

	i = 0;
	while (commands_string[i])
	{
		buffer = ft_str_create();
		reconstruct_space_helper(commands_string, i, buffer);
		free(commands_string[i]);
		commands_string[i] = ft_str_get_char_array(buffer, buffer->size);
		ft_str_free(buffer);
		i++;
	}
	return (1);
}
