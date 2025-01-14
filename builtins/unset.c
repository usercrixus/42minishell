/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:56:44 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/14 11:53:10 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	reconstruct_env(char **new_env, int i)
{
	int	j;

	j = 1;
	while (g_mini_env[j])
	{
		if (j < i)
		{
			new_env[j] = ft_strdup(g_mini_env[j]);
			if (!new_env[j])
				return (ft_free_split(new_env), 1);
		}
		else if (j > i)
		{
			new_env[j - 1] = ft_strdup(g_mini_env[j]);
			if (!new_env[j - 1])
				return (ft_free_split(new_env), 1);
		}
		j++;
	}
	new_env[j - 1] = NULL;
	ft_free_split(g_mini_env);
	g_mini_env = new_env;
	return (0);
}

int	delete_var(int i)
{
	int		j;
	char	**new_env;
	char	*stock_errno;

	j = ft_split_size(g_mini_env);
	stock_errno = ft_strdup(g_mini_env[0]);
	if (!stock_errno)
		return (1);
	new_env = malloc(j * sizeof(char *));
	if (!new_env)
		return (free(stock_errno), 1);
	new_env[0] = stock_errno;
	if (reconstruct_env(new_env, i) == 1)
		return (1);
	return (0);
}

int	unseting(char **command, int *rv, int j)
{
	int	i;

	i = 1;
	while (g_mini_env[i])
	{
		if (ft_strncmp(g_mini_env[i], command[j], ft_strlen(command[j])) \
		== 0 && g_mini_env[i][ft_strlen(command[j])] == '=')
		{
			if (delete_var(i) == 1)
				return (1);
			*rv = 0;
			break ;
		}
		else
			*rv = 1;
		i++;
	}
	return (0);
}

int	ft_unset(char **command)
{
	int	j;
	int	rv;
	int	rv_nul;

	rv = 0;
	j = 1;
	rv_nul = 0;
	while (command[j])
	{
		if (unseting(command, &rv, j) == 1)
			rv = 1;
		if (rv == 1)
			rv_nul = 1;
		j++;
	}
	if (rv_nul == 1)
		return (1);
	return (0);
}
