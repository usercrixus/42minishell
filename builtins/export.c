/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:10:09 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 16:04:29 by achaisne         ###   ########.fr       */
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

int	reconstruct_envv(char **new_env, char *var)
{
	int	i;

	i = 1;
	while (g_mini_env[i + 1])
	{
		new_env[i] = ft_strdup(g_mini_env[i]);
		if (!new_env[i])
			return (ft_free_split(new_env), 1);
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		return (ft_free_split(new_env), 1);
	new_env[i + 1] = ft_strdup(g_mini_env[i]);
	if (!new_env[i + 1])
		return (ft_free_split(new_env), 1);
	new_env[i + 2] = NULL;
	ft_free_split(g_mini_env);
	g_mini_env = new_env;
	return (0);
}

int	add_to_env(char *var)
{
	char	**new_env;
	int		size;
	char	*stock_errno;

	if (replace_if_exist(var) == 1)
		return (1);
	size = ft_split_size(g_mini_env);
	stock_errno = ft_strdup(g_mini_env[0]);
	if (!stock_errno)
		return (1);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return (1);
	new_env[0] = stock_errno;
	if (reconstruct_envv(new_env, var) == 1)
		return (1);
	return (0);
}

int	is_valid_env_id(char *arg)
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
		return (printf("export: '%s': not a valid identifier\n", arg), 0);
	ptr = arg;
	while (ptr < temp)
	{
		if (!((*ptr >= 'a' && *ptr <= 'z')
				|| (*ptr >= 'A' && *ptr <= 'Z')
				|| (*ptr >= '0' && *ptr <= '9')
				|| (*ptr == '_')))
			return (printf("export: '%s': not a valid identifier\n", arg), 0);
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
		if (is_valid_env_id(vars[i]))
		{
			if (add_to_env(vars[i]) == 1)
				return (1);
		}
		else
			rv = 1;
		i++;
	}
	return (rv);
}
