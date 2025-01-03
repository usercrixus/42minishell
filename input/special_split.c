/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:17:36 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 19:21:37 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	tab_size(const char *s, char c)
{
	int		i;
	int		size;
	char	is_active;

	is_active = 0;
	size = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && !is_active)
			size++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == is_active)
				is_active = 0;
			else if (!is_active && (s[i] == '\'' || (!is_active && s[i] == '"')))
				is_active = s[i];
			i++;
		}
	}
	return (size);
}

static char	*get_string(const char *s, int start, int end)
{
	char	*buffer;
	int		k;

	buffer = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!buffer)
		return (0);
	k = 0;
	while (k < end - start)
	{
		buffer[k] = s[k + start];
		k++;
	}
	buffer[k] = '\0';
	return (buffer);
}

static void	free_split(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static int	populate(char const *s, char **result, char c)
{
	int		i;
	int		j;
	int		start;
	char	*buffer;
	char	is_active;

	is_active = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		while (!is_active && s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && (s[i] != c || is_active))
		{
			if (!is_active && (s[i] == '\'' || s[i] == '"'))
				is_active = s[i];
			else if (is_active && s[i] == is_active)
				is_active = 0;
			i++;
		}
		if (start != i)
		{
			buffer = get_string(s, start, i);
			if (!buffer)
				return (0);
			result[j++] = buffer;
		}
	}
	result[j] = 0;
	return (1);
}

char	**special_split(char const *s, char c)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (tab_size(s, c) + 1));
	if (!result)
		return (0);
	if (!populate(s, result, c))
		free_split(result);
	return (result);
}
