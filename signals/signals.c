/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:35:53 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 18:29:21 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_not_blocking(int sig)
{
	(void)sig;
	if (g_command_running > 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	export_errno(130);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_blocking(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		export_errno(130);
	}
	else if (sig == SIGQUIT)
	{
		kill(g_command_running, sig);
		printf("Quit (Core Dumped)\n");
		export_errno(131);
	}
}

void	setup_signals_not_blocking_cmd(void)
{
	if (signal(SIGINT, handle_sigint_not_blocking) == SIG_ERR)
	{
		perror("signal(SIGINT)");
		ft_exit(0);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal(SIGQUIT)");
		ft_exit(0);
	}
}

void	setup_signals_blocking_cmd(void)
{
	if (signal(SIGINT, handle_sigint_blocking) == SIG_ERR)
	{
		perror("signal(SIGINT)");
		ft_exit(0);
	}
	if (signal(SIGQUIT, handle_sigint_blocking) == SIG_ERR)
	{
		perror("signal(SIGQUIT)");
		ft_exit(0);
	}
}

void	setup_signal(void)
{
	if (g_command_running == -1)
		setup_signals_not_blocking_cmd();
	else
		setup_signals_blocking_cmd();
}
