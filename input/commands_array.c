/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:30 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 03:33:31 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_command_array_size(char ***commands_array)
{
	int	i;

	i = 0;
	while (commands_array[i])
		i++;
	return (i);
}

void	destroy_commands_array(char ***commands_array)
{
	int	i;

	i = 0;
	while (commands_array[i])
	{
		ft_free_split(commands_array[i]);
		i++;
	}
	free(commands_array);
	commands_array = 0;
}

int	reconstruct_space_helper(char **commands_string, int i, t_str *buffer)
{
	int		j;
	char	quote;

	quote = 0;
	j = 0;
	while (commands_string[i][j])
	{
		if (commands_string[i][j] == '\'' || commands_string[i][j] == '"')
		{
			if (!quote)
				quote = commands_string[i][j];
			else if (quote == commands_string[i][j])
				quote = 0;
			j++;
		}
		else if (!quote && ft_strncmp(&commands_string[i][j], "<<", 2) == 0)
		{
			if (!ft_str_push(buffer, " << ", ft_strlen(" << ")))
				return (0);
			j += 2;
		}
		else if (!quote && ft_strncmp(&commands_string[i][j], "<", 1) == 0)
		{
			if (!ft_str_push(buffer, " < ", ft_strlen(" < ")))
				return (0);
			j++;
		}
		else if (!quote && ft_strncmp(&commands_string[i][j], ">>", 2) == 0)
		{
			if (!ft_str_push(buffer, " >> ", ft_strlen(" >> ")))
				return (0);
			j += 2;
		}
		else if (!quote && ft_strncmp(&commands_string[i][j], ">", 1) == 0)
		{
			if (!ft_str_push(buffer, " > ", ft_strlen(" > ")))
				return (0);
			j++;
		}
		else if (!ft_str_push(buffer, &commands_string[i][j++], 1))
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

char	***get_commands_array(char *line)
{
	char	**commands_string;
	char	***commands_array;
	int		split_size;
	int		i;

	commands_string = special_split(line, '|');
	if (!commands_string)
		return (0);
	if (!reconstruct_space(commands_string))
		return (0);
	split_size = ft_split_size(commands_string);
	commands_array = (char ***)malloc(sizeof(char ***) * (split_size + 1));
	if (!commands_array)
		return (0);
	i = 0;
	while (i < split_size)
	{
		commands_array[i] = special_split(commands_string[i], ' ');
		if (!commands_array[i])
			return (0);
		i++;
	}
	commands_array[i] = 0;
	ft_free_split(commands_string);
	return (commands_array);
}
