/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 01:20:48 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 00:04:32 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_errno(int code_error)
{
	char	*buff;

	buff = ft_itoa(code_error);
	if (mini_env[0])
		free(mini_env[0]);
	mini_env[0] = ft_strjoin("?=", buff);
	free(buff);
	return ;
}

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
	int		errno_value;

	command_buffer = command[0];
	command[0] = get_pathed_command(command[0]);
	if (!command[0])
	{
		ft_putstr_fd("Null command detected\n", 2);
		return (ft_free_split(command), -1);
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
	else if (execve(command[0], command, mini_env) == -1)
		return (perror(command[0]), ft_free_split(command), errno);
	return (0);
}
