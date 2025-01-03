/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:56:03 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 15:22:08 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_child(int pipefd[2], int output, int input, int is_redirect)
{
	if (output && dup2(output, STDOUT_FILENO) == -1)
		return (0);
	else if (!output && is_redirect && dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (0);
	if (input && dup2(input, STDIN_FILENO) == -1)
		return (0);
	if (close(pipefd[0]) == -1)
		return (0);
	if (close(pipefd[1]) == -1)
		return (0);
	return (1);
}

int	redirect_parent(int pipefd[2], int is_redirect)
{
	if (is_redirect && dup2(pipefd[0], STDIN_FILENO) == -1)
		return (0);
	if (close(pipefd[1]) == -1)
		return (0);
	if (close(pipefd[0]) == -1)
		return (0);
	return (1);
}

int	manage_child(int *pipefd, t_command_data *command_data, int limit, int max)
{
	if (!redirect_child(pipefd, command_data->output_array[limit],
			command_data->input_array[limit], limit != max))
		exit(1);
	launch_pipe_series(command_data, limit - 1, max);
	close_fds(command_data->input_array, max + 1);
	close_fds(command_data->output_array, max + 1);
	if (!execute_child(command_data->commands_array[limit]))
		exit(1);
	exit(0);
}

int	manage_parent(int *pipefd, t_command_data *command_data, int limit, int max)
{
	if (limit < max)
	{
		if (!redirect_parent(pipefd,
				limit != max && !command_data->input_array[limit + 1]))
			return (0);
	}
	else if (!redirect_parent(pipefd, limit != max))
		return (0);
	return (1);
}

int	launch_pipe_series(t_command_data *command_data, int limit, int max)
{
	int		pid;
	int		pipefd[2];

	if (limit < 0)
		return (1);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), 0);
	else if (pid == 0)
		manage_child(pipefd, command_data, limit, max);
	else if (pid > 0)
		manage_parent(pipefd, command_data, limit, max);
	return (1);
}
