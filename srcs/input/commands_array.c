/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:30 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 20:44:53 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	***get_commands_array(char *line)
{
	char	**commands_string;
	char	***commands_array;
	int		split_size;
	int		i;

	commands_string = special_split(line, '|');
	if (!commands_string)
		return (0);
	split_size = ft_split_size(commands_string);
	commands_array = (char ***)ft_calloc(sizeof(char ***), split_size + 1);
	if (!commands_array)
		return (ft_free_split(commands_string), (char ***)0);
	i = 0;
	while (i < split_size)
	{
		commands_array[i] = special_split(commands_string[i], ' ');
		if (!commands_array[i])
			return (ft_free_split(commands_string),
				destroy_commands_array(commands_array), (char ***)0);
		i++;
	}
	commands_array[i] = 0;
	return (ft_free_split(commands_string), commands_array);
}
