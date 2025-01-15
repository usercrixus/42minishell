/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:15:54 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/15 14:32:13 by gmorel           ###   ########.fr       */
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

void	ft_exit_main(char **cmds)
{
	if (cmds && cmds[1])
	{
		if (ft_split_size(cmds) > 2)
			printf("exit: too many arguments\n");
		else if (is_integer(cmds[1]))
			export_errno(ft_atoi(cmds[1]));
		else
			printf("exit: numeric argument required\n");
	}
}

void	exit_with_arg(char **cmds)
{
	int	buff;

	buff = ft_atoi(cmds[1]);
	ft_free_split(g_mini_env);
	rl_clear_history();
	if (ft_split_size(cmds) > 2)
	{
		ft_free_split(cmds);
		printf("exit: too many arguments\n");
	}
	else if (is_integer(cmds[1]))
	{
		ft_free_split(cmds);
		exit(buff);
	}
	else
	{
		ft_free_split(cmds);
		printf("exit: numeric argument required\n");
	}
}

void	ft_exit_child(char **cmds)
{
	int	buff;

	if (cmds && cmds[1])
	{
		exit_with_arg(cmds);
	}
	else
	{
		buff = ft_atoi(ft_get_env("?"));
		ft_free_split(g_mini_env);
		rl_clear_history();
		exit(buff);
	}
}
