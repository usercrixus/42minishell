/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:15:54 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 18:52:28 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_integer(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-')
	{
		i++;
		if (s[i] == '\0')
			return (0);
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (s[0] == '-' && ((i > 11)
			|| (i == 11 && ft_strncmp(s, "-2147483648", 11) > 0)))
		return (0);
	else if (s[0] != '-' && ((i > 10)
			|| (i == 10 && ft_strncmp(s, "2147483647", 10) > 0)))
		return (0);
	return (1);
}

void	ft_exit(char **cmds)
{
	int	status;

	if (!cmds)
	{
		status = ft_atoi(ft_get_env("?"));
		ft_free_split(g_mini_env);
		rl_clear_history();
		exit(status);
	}
	else
	{
		if (ft_split_size(cmds) > 2)
			printf("exit: too many arguments\n");
		else if (is_integer(cmds[1]))
		{
			status = ft_atoi(cmds[1]);
			ft_free_split(cmds);
			ft_free_split(g_mini_env);
			rl_clear_history();
			exit(status);
		}
		else
			printf("exit: numeric argument required\n");
	}
}
