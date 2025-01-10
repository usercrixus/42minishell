/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:59:01 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 15:15:41 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shift(char **command, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(command[i]);
		command[i] = 0;
		i++;
	}
	while (command[i])
	{
		command[i - size] = command[i];
		command[i] = 0;
		i++;
	}
}

char	*ft_get_env(const char *var_name)
{
	int		i;

	i = 0;
	while (g_mini_env[i])
	{
		if (ft_strncmp(var_name, g_mini_env[i], ft_strlen(var_name)) == 0 && \
		g_mini_env[i][ft_strlen(var_name)] == '=')
		{
			return (g_mini_env[i] + ft_strlen(var_name) + 1);
		}
		i++;
	}
	return (NULL);
}
