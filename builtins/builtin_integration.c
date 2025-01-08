/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:57:59 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/08 12:25:06 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_integration(char **command)
{
	if (ft_strncmp(command[0], "exit", ft_strlen("exit") + 1) == 0)
		ft_exit();
	else if (ft_strncmp(command[0], "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(command), 1);
	else if (ft_strncmp(command[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd(), 1);
	else if (ft_strncmp(command[0], "export", ft_strlen("export") + 1) == 0)
		return (ft_export(command), 1);
	else if (ft_strncmp(command[0], "echo", ft_strlen("echo") + 1) == 0)
		return (ft_echo(command), 1);
	else if (ft_strncmp(command[0], "unset", ft_strlen("unset") + 1) == 0)
		return (ft_unset(command), 1);
	else if (ft_strncmp(command[0], "env", ft_strlen("env") + 1) == 0)
		return (ft_env(command), 1);
	return (0);
}
