/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:00:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 02:16:58 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_heredoc_redirect(char **commands_array, int *fd_intput, int i)
{
	if (ft_strncmp(commands_array[i], "<<", 2) == 0
		&& ft_strlen(commands_array[i]) == 2)
	{
		*fd_intput = get_here_doc(commands_array[i + 1]);
		if (*fd_intput == -1)
			return (0);
		shift(commands_array + i, 2);
	}
	else if (ft_strncmp(commands_array[i], "<<", 2) == 0
		&& ft_strlen(commands_array[i]) > 2)
	{
		*fd_intput = get_here_doc(&commands_array[i][2]);
		if (*fd_intput == -1)
			return (0);
		shift(commands_array + i, 1);
	}
	return (1);
}

int	set_input_redirect(char **commands_array, int *fd_intput, int i)
{
	if (ft_strncmp(commands_array[i], "<", 1) == 0
		&& ft_strlen(commands_array[i]) == 1)
	{
		*fd_intput = open(commands_array[i + 1], O_RDONLY);
		if (*fd_intput == -1)
			return (0);
		shift(commands_array + i, 2);
	}
	else if ((ft_strncmp(commands_array[i], "<", 1) == 0
			&& ft_strlen(commands_array[i]) > 1))
	{
		*fd_intput = open(&commands_array[i][1], O_RDONLY);
		if (*fd_intput == -1)
			return (0);
		shift(commands_array + i, 1);
	}
	return (1);
}

int	set_input(char **commands_array, int *fd_intput)
{
	int	i;

	i = 0;
	while (commands_array[i])
	{
		if (ft_strncmp(commands_array[i], "<<", 2) == 0
			|| ft_strncmp(commands_array[i], "<", 1) == 0)
		{
			if (*fd_intput != 0 && !close(*fd_intput))
				return (0);
			if (!set_heredoc_redirect(commands_array, fd_intput, i))
				return (0);
			if (!set_input_redirect(commands_array, fd_intput, i))
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
			get_command_array_size(commands_array) + 1, sizeof(int));
	if (!input_array)
		return (0);
	i = 0;
	while (commands_array[i])
	{
		if (!set_input(commands_array[i], &input_array[i]))
			return (free(input_array), (int *)0);
		i++;
	}
	return (input_array);
}
