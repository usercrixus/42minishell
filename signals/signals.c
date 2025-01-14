/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:35:53 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 17:19:48 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
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

void	setup_signals(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("signal(SIGINT)");
		ft_exit();
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal(SIGQUIT)");
		ft_exit();
	}
}
