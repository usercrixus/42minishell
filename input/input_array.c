/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:00:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 01:13:12 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_array.h"

int	set_input(char **commands_array, int *fd_intput)
{
	int	i;

	i = 0;
	while (commands_array[i])
	{
		if (ft_strncmp(commands_array[i], "<<", 3) == 0
			|| ft_strncmp(commands_array[i], "<", 3) == 0)
		{
			if (is_syntax_error(commands_array[i + 1]))
				return (0);
			if (*fd_intput != 0 && !close(*fd_intput))
				return (0);
			if (ft_strncmp(commands_array[i], "<<", 3) == 0)
				*fd_intput = get_here_doc(commands_array[i + 1]);
			else
				*fd_intput = open(commands_array[i + 1], O_RDONLY);
			shift(commands_array + i);
		}
		else
			i++;
	}
	return (1);
}

int	*get_input_array(char ***commands_array)
{
	int	*input_array;
	int	i;

	input_array = (int *)ft_calloc(
			get_command_array_size(commands_array) + 1, sizeof(int));
	if (!input_array)
		return (0);
	i = 0;
	while (commands_array[i])
	{
		set_input(commands_array[i], &input_array[i]);
		i++;
	}
	return (input_array);
}
