/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:27:38 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 17:21:49 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_value(char *var, char *value, int i)
{
	int		j;
	char	**new_env;

	j = 0;
	if (!value)
		return (1);
	while (g_mini_env[j])
		j++;
	new_env = malloc((j + 1) * sizeof(char *));
	if (!new_env)
		return (1);
	j = 0;
	while (g_mini_env[j])
	{
		if (j != i)
			new_env[j] = ft_strdup(g_mini_env[j]);
		else
			new_env[j] = ft_strjoin(var, value);
		if (!new_env[j])
			return (ft_free_split(new_env), 1);
		j++;
	}
	new_env[j] = NULL;
	ft_free_split(g_mini_env);
	g_mini_env = new_env;
	return (0);
}

int	actualise_env(char *oldpwd)
{
	int		i;
	char	buff[50];

	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "OLDPWD", ft_strlen("OLDPWD")) == 0
			&& g_mini_env[i][ft_strlen("OLDPWD")] == '=')
			if (replace_value("OLDPWD=", oldpwd, i) == 1)
				return (1);
		i++;
	}
	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "PWD", ft_strlen("PWD")) == 0
			&& g_mini_env[i][ft_strlen("PWD")] == '=')
			if (replace_value("PWD=", getcwd(buff, 50), i) == 1)
				return (1);
		i++;
	}
	return (0);
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

int	go_to_desktop_and_more(char **command, char *old_pwd)
{
	char	**home;
	char	*cmd;
	char	*final_cmd;

	home = NULL;
	cmd = NULL;
	final_cmd = NULL;
	home = get_home_path();
	if (home == NULL)
		return (ft_putstr_fd("HOME not set\n", 2), 1);
	else if (command[1] && old_pwd)
	{
		cmd = ft_substr(command[1], 1, ft_strlen(command[1]));
		final_cmd = ft_strjoin(home[1], cmd);
		if (!cmd || !final_cmd)
			return (1);
		if (chdir(final_cmd) == -1)
			return (1);
	}
	else
	{
		if (chdir(home[1]) == -1)
			return (1);
	}
	free(final_cmd);
	free(cmd);
	return (ft_free_split(home), 0);
}

int	ft_cd(char **command)
{
	char	buff[50];
	char	*old_pwd;
	int		i;

	i = 0;
	old_pwd = ft_get_env("PWD");
	if (!old_pwd)
		old_pwd = getcwd(buff, 50);
	if (!old_pwd[0])
	{
		old_pwd = ft_strdup("");
		if (!old_pwd)
			return (1);
		i = 1;
	}
	if (!command[1] || command[1][0] == '~')
	{
		if (go_to_desktop_and_more(command, old_pwd) == 1)
			return (perror(command[1]), 1);
	}
	else if (!(getcwd(buff, 50)))
	{
		printf("chdir: error retrieving current directory: getcwd:");
		printf(" cannot access parent directories: No such file or directory\n");
		chdir(command[1]);
	}
	else if (chdir(command[1]) == -1)
		return (perror(command[1]), 1);
	if (actualise_env(old_pwd) == 1)
		return (1);
	if (i == 1)
		free(old_pwd);
	return (0);
}
