/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:56:44 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 11:57:34 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_var(int i)
{
	int		j;
	char	**new_env;
	char	*stock_errno;

	j = ft_split_size(mini_env);
	stock_errno = ft_strdup(mini_env[0]);
	new_env = malloc(j * sizeof(char *));
	new_env[0] = stock_errno;
	if (!new_env)
		return ;
	j = 1;
	while (mini_env[j])
	{
		if (j < i)
			new_env[j] = ft_strdup(mini_env[j]);
		else if (j > i)
			new_env[j - 1] = ft_strdup(mini_env[j]);
		j++;
	}
	new_env[j - 1] = NULL;
	ft_free_split(mini_env);
	mini_env = new_env;
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
		while (mini_env[i])
		{
			if (ft_strncmp(mini_env[i], command[j], ft_strlen(command[j])) == 0
				&& mini_env[i][ft_strlen(command[j])] == '=')
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
