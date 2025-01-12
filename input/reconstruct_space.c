/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 05:43:07 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 06:24:13 by achaisne         ###   ########.fr       */
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

int	reconstruct_space_helper(char *commands_string, t_str *buffer)
{
	int		i;
	char	quote;
	char	*value;

	quote = 0;
	i = 0;
	while (commands_string[i])
	{
		if (commands_string[i] == '\'' || commands_string[i] == '"')
			set_reconstruct_quote(&quote, commands_string[i]);
		else
		{
			set_value(quote, &commands_string[i], &value);
			if (value)
			{
				if (!ft_str_push(buffer, value, ft_strlen(value)))
					return (0);
				i += ft_strlen(value) - 2;
			}
		}
		if (!value && !ft_str_push(buffer, &commands_string[i++], 1))
			return (0);
	}
	return (1);
}

int	reconstruct_space(char *line)
{
	t_str	*buffer;

	buffer = ft_str_create();
	if(!buffer)
		return (0);
	if (!reconstruct_space_helper(commands_string, buffer))
		return (ft_str_free(buffer), 0);
	free(commands_string);
	commands_string = ft_str_get_char_array(buffer, buffer->size);
	if (!commands_string)
		return (ft_str_free(buffer), 0);
	ft_str_free(buffer);
	return (1);
}
