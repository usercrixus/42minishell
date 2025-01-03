/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 17:54:07 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_command_running = 0;

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	input_loop();
	return (0);
}
