/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:57:42 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 18:28:52 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <unistd.h>
# include "../42libft/ft_base/libft.h"
# include "../input/input.h"
# include "./../input/input.h"

extern char	**environ;
/**
 * launch a series of command separated by a pipe.
 * Typicaly, split on pipe '|' character
 * 
 * argv : array of commands string
 * limit : number of command -1 (typicaly the split size -1)
 * max : same as limit
 */
int		launch_pipe_series(t_command_data *command_data, int limit, int max);
/**
 * path and launch the command (with execve)
 * command : the command to execute
 */
int		execute_child(char **command);
/**
 * close all element of fds (fd array)
 * fds : array of fd
 * size : the size of fds
 */
void	close_fds(int *fds, int size);
/**
 * find the path corresponding to the command. If not found, return the command.
 * 
 * return : command pathed, if not found, command. 0 for error.
 */
char	*get_pathed_command(char *command);

#endif