/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:10:09 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/10 15:16:54 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_if_exist(char *arg)
{
	int		i;
	char	*key;

	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!key)
		return (1);
	i = 0;
	while (g_mini_env[i])
	{
		if (!ft_strncmp(g_mini_env[i], key, ft_strlen(key))
			&& g_mini_env[i][ft_strlen(key)] == '=')
		{
			free(g_mini_env[i]);
			g_mini_env[i] = ft_strdup(arg);
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
	size = ft_split_size(g_mini_env);
	stock_errno = ft_strdup(g_mini_env[0]);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return ;
	new_env[0] = stock_errno;
	i = 1;
	while (g_mini_env[i + 1])
	{
		new_env[i] = ft_strdup(g_mini_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = ft_strdup(g_mini_env[i]);
	new_env[i + 2] = NULL;
	ft_free_split(g_mini_env);
	g_mini_env = new_env;
	return ;
}

int	is_valid(char *arg)
{
	char	*temp;
	char	*ptr;

	temp = ft_strchr(arg, '=');
	if (!temp)
		return (0);
	if (temp == arg || *(temp - 1) == ' ')
		return (printf("export: '%s': not a valid identifier\n", arg), 0);
	if (!(arg[0] == '_' || (arg[0] >= 'a' && arg[0] <= 'z')
			|| (arg[0] >= 'A' && arg[0] <= 'Z')))
		return (0);
	ptr = arg;
	while (ptr < temp)
	{
		if (!((*ptr >= 'a' && *ptr <= 'z')
				|| (*ptr >= 'A' && *ptr <= 'Z')
				|| (*ptr >= '0' && *ptr <= '9')
				|| (*ptr == '_')))
			return (0);
		ptr++;
	}
	return (1);
}

int	ft_export(char **vars)
{
	int	i;
	int	rv;

	rv = 0;
	i = 1;
	while (vars[i])
	{
		if (is_valid(vars[i]))
			add_to_env(vars[i]);
		else
			rv = 1;
		i++;
	}
	return (rv);
}
