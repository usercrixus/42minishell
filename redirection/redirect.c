/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:18:18 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/30 16:11:55 by achaisne         ###   ########.fr       */
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

// int	redirect_here_doc(char **command)
// {

// }

int	redirect_truncate_output(char **command)
{
	int	fd_out;

	fd_out = open(command[ft_split_size(command) - 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
		return (command[ft_split_size(command) - 1], 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), 0);
	return (close(fd_out), 1);
}

int	redirect_append_output(char **command)
{
	int	fd_out;

	fd_out = open(command[ft_split_size(command) - 1], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd_out == -1)
		return (command[ft_split_size(command) - 1], 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), 0);
	return (close(fd_out), 1);
}

int	redirect(char **command)
{
	int	status;
	int	split_size;
	int	min_size;

	status = 0;
	split_size = ft_split_size(command);
	min_size = 2;
	if (split_size > min_size && ft_strncmp(command[0], "<", 1) == 0)
		if (redirect_input(command))
		{
			min_size += 2;
			status |= 0b1;
		}
	else if (split_size > min_size && ft_strncmp(command[0], "<<", 2) == 0)
		if (redirect_here_doc(command))
		{
			min_size += 2;
			status |= 0b1;
		}
	if (split_size > min_size && ft_strncmp(command[ft_split_size(command) - 2], ">", 1) == 0)
		if (redirect_truncate_output(command))
			status |= 0b10;
	else if (split_size > min_size && ft_strncmp(command[ft_split_size(command) - 2], ">>", 2) == 0)
		if (redirect_append_output(command))
			status |= 0b10;
	return (status);
}