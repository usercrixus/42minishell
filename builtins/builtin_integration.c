/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:57:59 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 18:45:58 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_child_executer(char **command)
{
	if (ft_strncmp(command[0], "exit", ft_strlen("exit") + 1) == 0)
		return (0);
	else if (ft_strncmp(command[0], "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(command));
	else if (ft_strncmp(command[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd());
	else if (ft_strncmp(command[0], "export", ft_strlen("export") + 1) == 0)
		return (ft_export(command));
	else if (ft_strncmp(command[0], "echo", ft_strlen("echo") + 1) == 0)
		return (ft_echo(command));
	else if (ft_strncmp(command[0], "unset", ft_strlen("unset") + 1) == 0)
		return (ft_unset(command));
	else if (ft_strncmp(command[0], "env", ft_strlen("env") + 1) == 0)
		return (ft_env(command));
	return (127);
}

int	builtin_main_executer(t_command_data *commands_data)
{
	if (ft_strncmp(commands_data->commands_array[0][0], "env", 4) == 0)
		return (ft_env(commands_data->commands_array[0]), 0);
	if (ft_strncmp(commands_data->commands_array[0][0], "export", 7) == 0)
		return (ft_export(commands_data->commands_array[0]), 0);
	if (ft_strncmp(commands_data->commands_array[0][0], "unset", 6) == 0)
		return (ft_unset(commands_data->commands_array[0]), 0);
	if (ft_strncmp(commands_data->commands_array[0][0], "cd", 3) == 0)
		return (ft_cd(commands_data->commands_array[0]), 0);
	if (ft_strncmp(commands_data->commands_array[0][0], "exit", 5) == 0)
		return (-1);
	return (127);
}
