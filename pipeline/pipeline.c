/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:56:03 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/31 02:20:56 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

int	execute_child(char *command_str)
{
	char	**command;
	char	*command_buffer;
	int		redirect_status;

	command = ft_split(command_str, ' ');
	if (!command)
		return (ft_putstr_fd("Split failed in execute_child\n", 2), 0);
	redirect_status = redirect(command);
	command_buffer = command[0];
	command[0] = pathed_command(command[0]);
	if (!command[0])
	{
		if (!redirect_status)
			ft_putstr_fd("Null command detected\n", 2);
		return (ft_free_split(command), 0);
	}
	if (command[0] != command_buffer)
		free(command_buffer);
	if (execve(command[0], command, environ) == -1)
	{
		perror(command[0]);
		ft_free_split(command);
		return (0);
	}
	return (1);
}

int	manage_child(int pipefd[2], int redirect)
{
	if (redirect && dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (0);
	if (close(pipefd[0]) == -1)
		return (0);
	if (close(pipefd[1]) == -1)
		return (0);
	return (1);
}

int	manage_parent(int pipefd[2], int redirect)
{
	if (redirect && dup2(pipefd[0], STDIN_FILENO) == -1)
		return (0);
	if (close(pipefd[1]) == -1)
		return (0);
	if (close(pipefd[0]) == -1)
		return (0);
	return (1);
}

int	launch_pipe_series(char **commands, int limit, int max)
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
	{
		if (!manage_child(pipefd, limit != max))
			exit(1);
		launch_pipe_series(commands, limit - 1, max);
		if (!execute_child(commands[limit]))
			exit(1);
		exit(0);
	}
	else if (pid > 0)
		if (!manage_parent(pipefd, limit != max))
			return (0);
	return (1);
}
