/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 12:48:12 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/prctl.h>
#include <sys/syscall.h>

volatile sig_atomic_t	g_command_running = 0;
char					**g_mini_env = NULL;

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
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!envp[0])
		return (0);
	setup_signals();
	init_mini_env(envp);
	input_loop();
	return (0);
}
