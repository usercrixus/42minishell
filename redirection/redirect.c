/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:18:18 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/30 23:56:43 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./redirect.h"

int	redirect_input(char **command)
{
	int	fd_in;

	fd_in = open(command[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror(command[1]);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			return (perror("Failed to open /dev/null"), 0);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(fd_in), 0);
	return (close(fd_in), 1);
}

int	redirect_here_doc(char **command)
{
	int	fd_in;

	if (!set_here_doc(command[1]))
		return (0);
	fd_in = open(command[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror(command[1]);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			return (perror("Failed to open /dev/null"), 0);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(fd_in), 0);
	if (unlink(command[1]) == -1)
		return (close(fd_in), 0);
	return (close(fd_in), 1);
}

int	redirect_truncate_output(char **command)
{
	int	fd_out;

	fd_out = open(command[ft_split_size(command) - 1],
			O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
		return (0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), 0);
	return (close(fd_out), 1);
}

int	redirect_append_output(char **command)
{
	int	fd_out;

	fd_out = open(command[ft_split_size(command) - 1],
			O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
		return (0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), 0);
	return (close(fd_out), 1);
}

int	redirect(char **command)
{
	int	status;
	int	split_size;

	status = 0;
	split_size = ft_split_size(command);
	if (split_size >= 2)
	{
		if (ft_strncmp(command[0], "<", 2) == 0 && redirect_input(command))
			status |= 0b01;
		else if (ft_strncmp(command[0], "<<", 3) == 0
			&& redirect_here_doc(command))
			status |= 0b01;
	}
	if ((status && split_size >= 4) || (!status && split_size >= 2))
	{
		if (ft_strncmp(command[split_size - 2], ">>", 3) == 0
			&& redirect_append_output(command))
			status |= 0b10;
		else if (ft_strncmp(command[split_size - 2], ">", 2) == 0
			&& redirect_truncate_output(command))
			status |= 0b10;
	}
	return (clean_command(command, status), status);
}
