/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:56:03 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 00:21:44 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_child(t_command_data *command_data, int i, int max)
{
	int		buffer_errno;

	if (command_data->input_array[i])
		dup2(command_data->input_array[i], STDIN_FILENO);
	if (command_data->output_array[i])
		dup2(command_data->output_array[i], STDOUT_FILENO);
	close_fds(command_data->input_array, max);
	close_fds(command_data->output_array, max);
	buffer_errno = execute_child(command_data->commands_array[i]);
	detroy_all(command_data);
	ft_exit(buffer_errno);
}

int	launch_pipe_series(t_command_data *command_data, int max)
{
	int		pid;
	int		i;

	i = 0;
	while (i < max)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
			manage_child(command_data, i, max);
		i++;
	}
	close_fds(command_data->input_array, max);
	close_fds(command_data->output_array, max);
	return (pid);
}
