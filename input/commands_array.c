/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:30 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 15:22:26 by gmorel           ###   ########.fr       */
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
}

char	***get_commands_array(char *line)
{
	char	**commands_string;
	char	***commands_array;
	int		split_size;
	int		i;

	commands_string = ft_split(line, '|');
	if (!commands_string)
		return (0);
	split_size = ft_split_size(commands_string);
	commands_array = (char ***)malloc(sizeof(char ***) * (split_size + 1));
	if (!commands_array)
		return (0);
	i = 0;
	while (i < split_size)
	{
		commands_array[i] = ft_split(commands_string[i], ' ');
		if (!commands_array[i])
			return (0);
		i++;
	}
	commands_array[i] = 0;
	ft_free_split(commands_string);
	return (commands_array);
}
