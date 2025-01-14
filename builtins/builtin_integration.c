/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:57:59 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/14 23:45:26 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_child_executer(char **cmds)
{
	if (ft_strncmp(cmds[0], "exit", ft_strlen("exit") + 1) == 0)
		return (ft_exit_child(cmds), 0);
	else if (ft_strncmp(cmds[0], "export", ft_strlen("export") + 1) == 0)
		return (ft_export(cmds));
	else if (ft_strncmp(cmds[0], "unset", ft_strlen("unset") + 1) == 0)
		return (ft_unset(cmds));
	else if (ft_strncmp(cmds[0], "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(cmds));
	else if (ft_strncmp(cmds[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmds[0], "echo", ft_strlen("echo") + 1) == 0)
		return (ft_echo(cmds));
	else if (ft_strncmp(cmds[0], "env", ft_strlen("env") + 1) == 0)
		return (ft_env(cmds));
	return (127);
}

int	builtin_main_executer(char **cmds)
{
	if (ft_strncmp(cmds[0], "exit", ft_strlen("exit") + 1) == 0)
		return (ft_exit_main(cmds), -1);
	if (ft_strncmp(cmds[0], "export", ft_strlen("export") + 1) == 0)
		return (ft_export(cmds));
	if (ft_strncmp(cmds[0], "unset", ft_strlen("unset") + 1) == 0)
		return (ft_unset(cmds));
	if (ft_strncmp(cmds[0], "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(cmds));
	if (ft_strncmp(cmds[0], "env", ft_strlen("env") + 1) == 0)
		return (ft_env(cmds));
	if (ft_strncmp(cmds[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd());
	return (127);
}
