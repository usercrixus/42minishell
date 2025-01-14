/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:56:03 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/14 23:30:40 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(int *fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (fds[i] > 0)
			close(fds[i]);
		i++;
	}
}

int	execute_child(char **command)
{
	char	*command_buffer;
	int		errno_value;

	command_buffer = command[0];
	command[0] = get_pathed_command(command[0]);
	if (!command[0])
	{
		ft_putstr_fd("Null command detected\n", 2);
		return (-1);
	}
	if (command[0] != command_buffer)
		free(command_buffer);
	if (access(command[0], F_OK) == -1)
	{
		errno_value = builtin_child_executer(command);
		if (errno_value == 127)
		{
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		return (errno_value);
	}
	else if (execve(command[0], command, g_mini_env) == -1)
		return (perror(command[0]), errno);
	return (0);
}

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
	destroy_all(command_data);
	export_errno(buffer_errno);
	ft_exit_child(0);
}

int	launch_pipe_series(t_command_data *command_data, int max)
{
	int	pid;
	int	i;
	int	command_size;
	int	stat_loc;

	i = 0;
	while (i < max)
	{
		pid = fork();
		g_command_running = pid;
		if (pid == -1)
			return (perror("Error launching pipe: "), 0);
		else if (pid == 0)
			manage_child(command_data, i, max);
		i++;
	}
	close_fds(command_data->input_array, max);
	close_fds(command_data->output_array, max);
	command_size = get_triple_array_size(command_data->commands_array);
	while (command_size-- > 0)
	{
		if (waitpid(-1, &stat_loc, 0) == pid && WIFEXITED(stat_loc))
			export_errno(WEXITSTATUS(stat_loc));
	}
	return (pid);
}
