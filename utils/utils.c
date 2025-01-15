/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 20:34:56 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/15 00:43:46 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_triple_array_size(char ***commands_array)
{
	int	i;

	i = 0;
	while (commands_array[i])
		i++;
	return (i);
}

int	get_char_occurence(char *str, char c)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			result++;
		i++;
	}
	return (result);
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

void	export_errno(int code_error)
{
	char	*buff;

	buff = ft_itoa(code_error);
	if (!buff)
		return ;
	if (g_mini_env[0])
		free(g_mini_env[0]);
	g_mini_env[0] = ft_strjoin("?=", buff);
	free(buff);
	return ;
}
