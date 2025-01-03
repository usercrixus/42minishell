/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 16:27:19 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_command_running = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("%s\n", envp[0]);
	printf("%s\n", environ[0]);
	//init_minishell(envp);
	input_loop();
	return (0);
}
