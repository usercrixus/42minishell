/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:00:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 20:33:28 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_output(char **commands_array, int *fd_output)
{
	int	i;
	int	flags;

	i = 0;
	while (commands_array[i])
	{
		if (ft_strncmp(commands_array[i], ">>", 3) == 0
			|| ft_strncmp(commands_array[i], ">", 3) == 0)
		{
			if (is_syntax_error(commands_array[i + 1]))
				return (0);
			if (*fd_output != 0 && !close(*fd_output))
				return (0);
			if (ft_strncmp(commands_array[i], ">", 3) == 0)
				flags = O_CREAT | O_WRONLY | O_TRUNC;
			else
				flags = O_CREAT | O_WRONLY | O_APPEND;
			*fd_output = open(commands_array[i + 1], flags, S_IRUSR | S_IWUSR);
			shift(commands_array + i, 2);
		}
		else
			i++;
	}
	return (1);
}

int	*get_output_array(char ***commands_array)
{
	int	*output_array;
	int	i;

	output_array = ft_calloc(
			get_command_array_size(commands_array) + 1, sizeof(int));
	if (!output_array)
		return (0);
	i = 0;
	while (commands_array[i])
	{
		set_output(commands_array[i], &output_array[i]);
		i++;
	}
	return (output_array);
}
