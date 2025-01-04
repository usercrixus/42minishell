/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:08:02 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/04 20:09:51 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_start(char const *s, char *is_active, int *i, char c)
{
	while (!(*is_active) && s[*i] && s[*i] == c)
		(*i)++;
	return (*i);
}

void	set_end(char const *s, char *is_active, int *i, char c)
{
	while (s[*i] && (s[*i] != c || *is_active))
	{
		if (!(*is_active) && (s[*i] == '\'' || s[*i] == '"'))
			*is_active = s[*i];
		else if (*is_active && s[*i] == *is_active)
			*is_active = 0;
		(*i)++;
	}
}
