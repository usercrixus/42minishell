/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:59:01 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/07 16:32:02 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_syntax_error(char *command)
{
	if (!command)
		return (1);
	else if (ft_strncmp(command, "<<", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "<", 2) == 0)
		return (1);
	return (0);
}

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
		command[i - 2] = command[i];
		command[i] = 0;
		i++;
	}
}

char	*ft_get_env(const char *var_name)
{
	int		i;
	char	*var_value;

	i = 0;
	while (mini_env[i])
	{
		if (ft_strncmp(var_name, mini_env[i], ft_strlen(var_name)) == 0 && \
		mini_env[i][ft_strlen(var_name)] == '=')
		{
			var_value = ft_substr(mini_env[i], ft_strlen(var_name) + 1, \
			ft_strlen(mini_env[i]) - ft_strlen(var_name) - 1);
			return (var_value);
		}
		i++;
	}
	return (NULL);
}
