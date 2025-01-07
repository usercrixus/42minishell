/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:10:09 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/07 17:48:01 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_if_exist(char *arg)
{
	int		i;
	char 	*key;

	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!key)
		return (1);
	i = 0;
	while (mini_env[i])
	{
		if (!ft_strncmp(mini_env[i], key, ft_strlen(key)) && mini_env[i][ft_strlen(key)] == '=')
		{
			free(mini_env[i]);
			mini_env[i] = ft_strdup(arg);
			free(key);
			return (1);
		}
        i++;
	}
	free(key);
	return (0);
}

void	add_to_env(char *var)
{
	char	**new_env;
	int		size;
	int		i;
	char	*stock_errno;

	if (replace_if_exist(var))
		return ;
	size = ft_split_size(mini_env);
	stock_errno = ft_strdup(mini_env[0]);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return ;
	new_env[0] = stock_errno;
	i = 1;
	while (mini_env[i + 1])
	{
		new_env[i] = ft_strdup(mini_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = ft_strdup(mini_env[i]);
	new_env[i + 2] = NULL;
	ft_free_split(mini_env);
	mini_env = new_env;
	return ;
}

// int	is_valid(char *arg)
// {
	
// }

void    ft_export(char **vars)
{
	int	i;

	i = 1;
	while (vars[i])
	{
		// if (is_valid(vars[i]))
			add_to_env(vars[i]);
		i++;
	}
	return ;
}
