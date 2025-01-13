/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:56:44 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 12:33:19 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reconstruct_env(char **new_env, int i)
{
	int	j;

	j = 1;
	while (g_mini_env[j])
	{
		if (j < i)
		{
			new_env[j] = ft_strdup(g_mini_env[j]);
			if (!new_env[j])
				return ;
		}
		else if (j > i)
		{
			new_env[j - 1] = ft_strdup(g_mini_env[j]);
			if (!new_env[j - 1])
				return ;
		}
		j++;
	}
	new_env[j - 1] = NULL;
	ft_free_split(g_mini_env);
	g_mini_env = new_env;
	return ;
}

void	delete_var(int i)
{
	int		j;
	char	**new_env;
	char	*stock_errno;

	j = ft_split_size(g_mini_env);
	stock_errno = ft_strdup(g_mini_env[0]);
	if (!stock_errno)
		return ;
	new_env = malloc(j * sizeof(char *));
	if (!new_env)
		return ;
	new_env[0] = stock_errno;
	reconstruct_env(new_env, i);
	return ;
}

int	ft_unset(char **command)
{
	int	i;
	int	j;
	int	rv;

	rv = 0;
	j = 1;
	while (command[j])
	{
		i = 1;
		while (g_mini_env[i])
		{
			if (ft_strncmp(g_mini_env[i], command[j], ft_strlen(command[j])) \
			== 0 && g_mini_env[i][ft_strlen(command[j])] == '=')
			{
				delete_var(i);
				rv = 0;
				break ;
			}
			else
				rv = 1;
			i++;
		}
		j++;
	}
	return (rv);
}
