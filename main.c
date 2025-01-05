/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/05 15:41:26 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/prctl.h>
#include <sys/syscall.h>

volatile sig_atomic_t g_command_running = 0;

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	input_loop();
	return (0);
}
