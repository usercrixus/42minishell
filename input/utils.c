/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:59:01 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 00:51:31 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

void	shift(char **command)
{
	int	i;

	free(command[0]);
	command[0] = 0;
	free(command[1]);
	command[1] = 0;
	i = 2;
	while (command[i])
	{
		command[i - 2] = command[i];
		command[i] = 0;
		i++;
	}
}
