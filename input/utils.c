/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:59:01 by achaisne          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/03 17:18:00 by achaisne         ###   ########.fr       */
=======
/*   Updated: 2025/01/03 17:13:50 by gmorel           ###   ########.fr       */
>>>>>>> 4e9222793a36aff931ba44edd2e3cf123f03efa2
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
