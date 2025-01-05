/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:10:09 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/05 00:58:52 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_to_env(char *var)
{
	char	**new_env;
	int		size;
	int		i;
	char 	*key;
	
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
    free(key);
	size = ft_split_size(environ);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[i] = var;
	new_env[i + 1] = NULL;
	return (ft_free_split(environ), new_env);
}

void    ft_export(char **vars)
{
	int	i;

	//free(vars[0]);
	i = 1;
	while (vars[i])
	{
		environ = add_to_env(vars[i]);
		i++;
	}
	return ;
}
