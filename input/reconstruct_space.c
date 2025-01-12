/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 05:43:07 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 20:38:05 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (set_quote(&quote, commands_string))
		{
			if (!ft_str_push(buffer, &commands_string[i++], 1))
				return (0);
		}
		else
		{
			set_value(quote, &commands_string[i], &value);
			if (value)
			{
				if (!ft_str_push(buffer, value, ft_strlen(value)))
					return (0);
				i += ft_strlen(value) - 2;
			}
			else if (!ft_str_push(buffer, &commands_string[i++], 1))
				return (0);
		}
	}
	return (1);
}

char	*get_reconstruct_space(char *commands_string)
{
	t_str	*buffer;
	char	*result;

	buffer = ft_str_create();
	if (!buffer)
		return (0);
	if (!reconstruct_space_helper(commands_string, buffer))
		return (ft_str_free(buffer), NULL);
	result = ft_str_get_char_array(buffer, buffer->size);
	if (!result)
		return (ft_str_free(buffer), NULL);
	ft_str_free(buffer);
	return (result);
}
