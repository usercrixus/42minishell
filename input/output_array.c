/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:00:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 21:38:40 by achaisne         ###   ########.fr       */
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
			if (*fd_output != 0 && close(*fd_output) == -1)
				return (0);
			if (ft_strncmp(commands_array[i], ">", 2) == 0)
				flags = O_CREAT | O_WRONLY | O_TRUNC;
			else
				flags = O_CREAT | O_WRONLY | O_APPEND;
			*fd_output = open(commands_array[i + 1], flags, S_IRUSR | S_IWUSR);
			if (*fd_output == -1)
				return (perror("output open error:"), 0);
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
			get_triple_array_size(commands_array) + 1, sizeof(int));
	if (!output_array)
		return (0);
	i = 0;
	while (commands_array[i])
	{
		if (!set_output(commands_array[i], &output_array[i]))
			return (free(output_array), (int *)0);
		if (!commands_array[i][0])
		{
			commands_array[i][0] = ft_strdup("true");
			if (!commands_array[i][0])
				return (free(output_array), (int *)0);
		}
		i++;
	}
	return (output_array);
}
