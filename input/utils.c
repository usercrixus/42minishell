/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:59:01 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 17:18:00 by achaisne         ###   ########.fr       */
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
	}
	while (command[i])
	{
		command[i - 2] = command[i];
		command[i] = 0;
		i++;
	}
}
