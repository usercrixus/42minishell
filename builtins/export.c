/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:10:09 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/06 17:17:02 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_to_env(char *var)
{
	char	**new_env;
	int		size;
	int		i;
/*	char 	*key;
	
    key = ft_substr(var, 0, ft_strchr(var, '=') - var);
    if (!key)
        return (NULL);
    i = 0;
    while (environ[i])
    {
        if (!ft_strncmp(environ[i], key, ft_strlen(key)) && environ[i][ft_strlen(key)] == '=')
        {
            free(environ[i]);
            environ[i] = ft_strdup(var);
            free(key);
            return (environ);
        }
        i++;
    }
    free(key);*/
	size = ft_split_size(mini_env);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (mini_env[i])
	{
		new_env[i] = mini_env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	return (ft_free_split(mini_env), new_env);
}

void    ft_export(char **vars)
{
	int	i;

	i = 1;
	while (vars[i])
	{
		add_to_env(vars[i]);
		i++;
	}
	return ;
}
