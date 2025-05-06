/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:47:20 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/11 19:59:00 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_charset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	start_index(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (is_in_charset(s1[i], set))
			i++;
		else
			break ;
	}
	return (i);
}

static int	end_index(const char *s1, const char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		if (is_in_charset(s1[i], set))
			i--;
		else
			break ;
	}
	return (i + 1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		s1_start;
	int		s1_end;
	char	*result;
	int		i;

	s1_start = start_index(s1, set);
	s1_end = end_index(s1, set);
	if (s1_start > s1_end)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (s1_end - s1_start + 1));
	if (!result)
		return (0);
	i = s1_start;
	while (i < s1_end)
	{
		result[i - s1_start] = s1[i];
		i++;
	}
	result[i - s1_start] = '\0';
	return (result);
}
