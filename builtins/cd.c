/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:27:38 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 14:33:57 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	actualise_env(char *oldpwd)
{
	char	buff[50];
	char	**cmd;

	cmd = malloc(3 * sizeof(char *));
	cmd[0] = ft_strdup("export");
	if (!cmd[0])
		return (ft_free_split(cmd));
	cmd[1] = ft_strjoin("PWD=", getcwd(buff, 50));
	if (!cmd[1])
		return (ft_free_split(cmd));
	cmd[2] = NULL;
	ft_export(cmd);
	ft_free_split(cmd);
	cmd = malloc(3 * sizeof(char *));
	cmd[0] = ft_strdup("export");
	if (!cmd[0])
		return (ft_free_split(cmd));
	cmd[1] = ft_strjoin("OLDPWD=", oldpwd);
	if (!cmd[1])
		return (ft_free_split(cmd));
	cmd[2] = NULL;
	ft_export(cmd);
	ft_free_split(cmd);
	return ;
}

char	**get_home_path(void)
{
	int		i;
	char	**temp;

	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "HOME=", 5) == 0)
		{
			temp = ft_split(g_mini_env[i], '=');
			return (temp);
		}
		i++;
	}
	return (NULL);
}

void	go_to_desktop_and_more(char **command, char *old_pwd)
{
	char	**home;
	char	*cmd;
	char	*final_cmd;

	home = NULL;
	cmd = NULL;
	final_cmd = NULL;
	home = get_home_path();
	if (home == NULL)
		return (ft_putstr_fd("HOME not set\n", 2), (void)0);
	else if (command[1] && old_pwd)
	{
		cmd = ft_substr(command[1], 1, ft_strlen(command[1]));
		final_cmd = ft_strjoin(home[1], cmd);
		if (!cmd || !final_cmd)
			return ;
		chdir(final_cmd);
	}
	else
		chdir(home[1]);
	free(final_cmd);
	free(cmd);
	return (ft_free_split(home));
}

int	ft_cd(char **command)
{
	char	buff[50];
	char	*old_pwd;

	old_pwd = getcwd(buff, 50);
	if (!command[1] || command[1][0] == '~')
		go_to_desktop_and_more(command, old_pwd);
	else if (!old_pwd)
	{
		printf("chdir: error retrieving current directory: getcwd:");
		printf(" cannot access parent directories: No such file or directory\n");
		chdir(command[1]);
	}
	else if (chdir(command[1]) == -1)
	{
		perror(command[1]);
		return (1);
	}
	actualise_env(old_pwd);
	return (0);
}
