/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:21:01 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 15:22:11 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(void)
{
	int		i;
	char	*line;
	char	**paths;

	i = 0;
	line = environ[i];
	while (ft_strncmp("PATH=", line, ft_strlen("PATH=")) != 0)
	{
		i++;
		line = environ[i];
	}
	if (ft_strncmp("PATH=", line, ft_strlen("PATH=")) != 0)
		return (0);
	line += ft_strlen("PATH=");
	paths = ft_split(line, ':');
	if (!paths)
		return (0);
	return (paths);
}

char	*get_pathed_command(char *command)
{
	char	*command_pathed;
	char	*path;
	char	**paths;
	int		i;

	if (!command)
		return (0);
	paths = get_path();
	if (!paths)
		return (command);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		if (!path)
			return (command);
		command_pathed = ft_strjoin(path, command);
		free(path);
		if (!command_pathed)
			return (command);
		if (access(command_pathed, F_OK) == 0)
			return (ft_free_split(paths), command_pathed);
		free(command_pathed);
	}
	return (ft_free_split(paths), command);
}
