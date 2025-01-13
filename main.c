/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 17:03:24 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/prctl.h>
#include <sys/syscall.h>

volatile sig_atomic_t	g_command_running = 0;
char					**g_mini_env = NULL;

void	create_shlvl(void)
{
	int		i;
	char	**new_env;

	i = ft_split_size(g_mini_env);
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return ;
	i = 1;
	while (g_mini_env[i + 1])
	{
		new_env[i] = ft_strdup(g_mini_env[i]);
		if (!new_env[i])
			return (ft_free_split(new_env));
		i++;
	}
	new_env[i] = ft_strdup("SHLVL=1");
	if (!new_env[i])
		return (ft_free_split(new_env));
	new_env[i + 1] = ft_strdup(g_mini_env[i]);
	if (!new_env[i + 1])
		return (ft_free_split(new_env));
	new_env[i + 2] = NULL;
	ft_free_split(g_mini_env);
	g_mini_env = new_env;
	return ;
}

int	replace_shlvl(void)
{
	int		i;
	int		new;
	char	*value;

	i = 0;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], "SHLVL=", 6) == 0)
		{
			new = ft_atoi(ft_strchr(g_mini_env[i], '=') + 1) + 1;
			free(g_mini_env[i]);
			if (new >= 1000)
			{
				printf("warning: shell level (%d) too high, resetting to 1\n", \
				new);
				new = 1;
			}
			value = ft_itoa(new);
			g_mini_env[i] = ft_strjoin("SHLVL=", value);
			return (free(value), 1);
		}
		i++;
	}
	return (create_shlvl(), 1);
}

void	init_mini_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_mini_env = malloc((i + 2) * sizeof(char *));
	g_mini_env[0] = ft_strdup("?=0");
	if (!g_mini_env[0])
		return (free(g_mini_env));
	i = 1;
	while (envp[i])
	{
		g_mini_env[i] = ft_strdup(envp[i]);
		if (!g_mini_env[i])
			return (ft_free_split(g_mini_env));
		i++;
	}
	g_mini_env[i] = NULL;
	if (!replace_shlvl())
		return ;
	return ;
}

void	init_no_envp(void)
{
	char	buff[50];

	g_mini_env = malloc(5 * sizeof(char *));
	g_mini_env[0] = ft_strdup("?=0");
	if (!g_mini_env[0])
		return (free(g_mini_env));
	g_mini_env[1] = ft_strjoin("PWD=", getcwd(buff, 50));
	if (!g_mini_env[1])
		return (ft_free_split(g_mini_env));
	g_mini_env[2] = ft_strdup("SHLVL=1");
	if (!g_mini_env[2])
		return (ft_free_split(g_mini_env));
	g_mini_env[3] = NULL;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	setup_signals();
	if (!envp[0])
		init_no_envp();
	else
		init_mini_env(envp);
	input_loop();
	return (0);
}
