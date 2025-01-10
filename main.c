/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 02:05:07 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/prctl.h>
#include <sys/syscall.h>

volatile sig_atomic_t	g_command_running = 0;
char					**mini_env = NULL;

void	init_mini_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	mini_env = malloc((i + 2) * sizeof(char *));
	mini_env[0] = ft_strdup("?=0");
	i = 1;
	while (envp[i])
	{
		mini_env[i] = ft_strdup(envp[i]);
		i++;
	}
	mini_env[i] = NULL;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	setup_signals();
	init_mini_env(envp);
	input_loop();
	return (0);
}
