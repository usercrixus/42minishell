/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:27:38 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/14 12:29:13 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_value(char **new_env, char *var, char *value, int i)
{
	int		j;

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
	char	**new_env;

	new_env = NULL;
	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "OLDPWD", ft_strlen("OLDPWD")) == 0
			&& g_mini_env[i][ft_strlen("OLDPWD")] == '=')
			if (replace_value(new_env, "OLDPWD=", oldpwd, i) == 1)
				return (1);
		i++;
	}
	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "PWD", ft_strlen("PWD")) == 0
			&& g_mini_env[i][ft_strlen("PWD")] == '=')
			if (replace_value(new_env, "PWD=", getcwd(buff, 50), i) == 1)
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
		if (create_cmd(cmd, final_cmd, home, command) == 1)
			return (ft_free_split(home), 1);
	}
	else
	{
		if (chdir(home[1]) == -1)
			return (ft_free_split(home), 1);
	}
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
	if (!command[1] || command[1][0] == '~')
	{
		if (go_to_desktop_and_more(command, old_pwd) == 1)
			return (perror(command[1]), 1);
	}
	else if (!(getcwd(buff, 50)))
		error_directory(command);
	else if (chdir(command[1]) == -1)
		return (perror(command[1]), 1);
	if (actualise_env(old_pwd) == 1)
		return (1);
	return (0);
}
