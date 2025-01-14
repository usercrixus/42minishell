/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:00:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/14 17:27:16 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shift_command(char **commands_array, int *fd_input, int i)
{
	if (*fd_input != 0 && close(*fd_input) == -1)
		return (0);
	if (ft_strncmp(commands_array[i], "<<", 3) == 0)
	{
		*fd_input = get_here_doc(commands_array[i + 1]);
		if (*fd_input == -1)
			return (0);
	}
	else if (ft_strncmp(commands_array[i], "<", 2) == 0)
		*fd_input = open(commands_array[i + 1], O_RDONLY);
	if (*fd_input == -1)
		return (0);
	shift(commands_array + i, 2);
	return (1);
}

int	set_input(char **commands_array, int *fd_intput)
{
	int	i;

	i = 0;
	while (commands_array[i])
	{
		if (ft_strncmp(commands_array[i], "<<", 3) == 0
			|| ft_strncmp(commands_array[i], "<", 2) == 0)
		{
			if (!shift_command(commands_array, fd_intput, i))
				return (0);
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
			get_triple_array_size(commands_array) + 1, sizeof(int));
	if (!input_array)
		return (0);
	i = 0;
	while (commands_array[i])
	{
		if (!set_input(commands_array[i], &input_array[i]))
			return (free(input_array), (int *)0);
		if (!commands_array[i][0])
		{
			commands_array[i][0] = ft_strdup("true");
			if (!commands_array[i][0])
				return (free(input_array), (int *)0);
		}
		i++;
	}
	return (input_array);
}
