/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:32:19 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/31 00:01:22 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

void	clean_command(char **command, int status)
{
	int	split_size;
	int	i;

	if ((status & 0b01) == 0b01)
	{
		free(command[0]);
		command[0] = 0;
		free(command[1]);
		command[1] = 0;
		i = 2;
		while (command[i])
		{
			command[i - 2] = command[i];
			i++;
		}
		command[i - 2] = 0;
	}
	if ((status & 0b10) == 0b10)
	{
		split_size = ft_split_size(command);
		free(command[split_size - 2]);
		command[split_size - 2] = 0;
		free(command[split_size - 1]);
		command[split_size - 1] = 0;
	}
}
