/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 01:20:48 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/04 22:23:49 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(int *fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (fds[i])
			close(fds[i]);
		i++;
	}
}

int	execute_child(char **command)
{
	char	*command_buffer;

	command_buffer = command[0];
	command[0] = get_pathed_command(command[0]);
	if (!command[0])
	{
		ft_putstr_fd("Null command detected\n", 2);
		return (ft_free_split(command), 0);
	}
	if (command[0] != command_buffer)
		free(command_buffer);
	if (access(command[0], F_OK) == -1)
	{
		if (!builtin_integration(command))
			return (ft_putstr_fd(command[0], 2),
				ft_putstr_fd(": command not found\n", 2), 0);
	}
	else if (execve(command[0], command, environ) == -1)
	{
		perror(command[0]);
		ft_free_split(command);
		return (0);
	}
	return (1);
}
