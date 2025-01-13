/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:27:38 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 16:20:58 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_value(char *var, char *value, int i)
{
	int		j;
	char	**new_env;

	j = 0;
	if (!value)
		return ;
	while (g_mini_env[j])
		j++;
	new_env = malloc((j + 1) * sizeof(char *));
	if (!new_env)
		return ;
	j = 0;
	while (g_mini_env[j])
	{
		if (j != i)
			new_env[j] = ft_strdup(g_mini_env[j]);
		else
			new_env[j] = ft_strjoin(var, value);
		if (!new_env[j])
			return ;
		j++;
	}
	new_env[j] = NULL;
	ft_free_split(g_mini_env);
	g_mini_env = new_env;
}

void	actualise_env(char *oldpwd)
{
	int		i;
	char	buff[50];

	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "OLDPWD", ft_strlen("OLDPWD")) == 0
			&& g_mini_env[i][ft_strlen("OLDPWD")] == '=')
			replace_value("OLDPWD=", oldpwd, i);
		i++;
	}
	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "PWD", ft_strlen("PWD")) == 0
			&& g_mini_env[i][ft_strlen("PWD")] == '=')
			replace_value("PWD=", getcwd(buff, 50), i);
		i++;
	}
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

	old_pwd = ft_get_env("PWD");
	if (!old_pwd)
		old_pwd = getcwd(buff, 50);
	if (!old_pwd[0])
		old_pwd = ft_strdup("");
	if (!command[1] || command[1][0] == '~')
		go_to_desktop_and_more(command, old_pwd);
	else if (!(getcwd(buff, 50)))
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
	if (old_pwd && old_pwd[0] == '\0')
		free(old_pwd);
	return (0);
}
