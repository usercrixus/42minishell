/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 15:37:58 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_command_running = 0;

void	init_minishell(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	environ = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		environ[i] = ft_strdup(envp[i]);
		i++;
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	(void)argv;
	init_minishell(envp);
	input_loop();
	return (0);
}
