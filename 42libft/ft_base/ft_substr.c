/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:19:17 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/18 14:54:03 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_string;
	int				final_len;
	unsigned int	s_len;
	unsigned int	i;

	s_len = ft_strlen(s);
	if (start > s_len)
		final_len = 0;
	else if (s_len - start > len)
		final_len = len;
	else
		final_len = s_len - start;
	sub_string = (char *)malloc(sizeof(char) * (final_len + 1));
	if (!sub_string)
		return (0);
	i = start;
	while (i < start + final_len)
	{
		sub_string[i - start] = s[i];
		i++;
	}
	sub_string[i - start] = '\0';
	return (sub_string);
}
