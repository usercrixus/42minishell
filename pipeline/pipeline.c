/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:56:03 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/08 03:08:48 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	launch_pipe_series(t_command_data *command_data, int max)
{
	int		pid;
	int		i;
	int		buffer_errno;

	i = 0;
	while (i < max)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
		{
			if (command_data->input_array[i])
				dup2(command_data->input_array[i], STDIN_FILENO);
			if (command_data->output_array[i])
				dup2(command_data->output_array[i], STDOUT_FILENO);
			close_fds(command_data->input_array, max);
			close_fds(command_data->output_array, max);
			buffer_errno = execute_child(command_data->commands_array[i]);
			if (buffer_errno == -1)
			{
				free(command_data->input_array);
				free(command_data->output_array);
				destroy_commands_array(command_data->commands_array);
				exit(buffer_errno);
			}
		}
		i++;
	}
	close_fds(command_data->input_array, max);
	close_fds(command_data->output_array, max);
	return (pid);
}
