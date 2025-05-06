/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:10:26 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 20:35:32 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_pipe_array(t_command_data *commands_data)
{
	int	pipefd[2];
	int	size;
	int	i;

	size = get_triple_array_size(commands_data->commands_array);
	i = 1;
	while (i < size)
	{
		if (pipe(pipefd) == -1)
			return (0);
		if (commands_data->input_array[i] == 0)
			commands_data->input_array[i] = pipefd[0];
		else
			close(pipefd[0]);
		if (commands_data->output_array[i - 1] == 0)
			commands_data->output_array[i - 1] = pipefd[1];
		else
			close(pipefd[1]);
		i++;
	}
	return (1);
}
