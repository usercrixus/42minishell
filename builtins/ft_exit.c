/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:15:54 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 23:44:32 by achaisne         ###   ########.fr       */
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

void	ft_exit_child(char **cmds)
{
	if (cmds && cmds[1])
	{
		if (ft_split_size(cmds) > 2)
			printf("exit: too many arguments\n");
		else if (is_integer(cmds[1]))
			exit(ft_atoi(cmds[1]));
		else
			printf("exit: numeric argument required\n");
	}
	else
		exit(ft_atoi(ft_get_env("?")));
}
