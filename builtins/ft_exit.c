/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:15:54 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 14:46:48 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(void)
{
	int	status;

	status = ft_atoi(ft_get_env("?"));
	ft_free_split(g_mini_env);
	rl_clear_history();
	exit(status);
}
