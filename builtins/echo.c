/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:54:45 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/05 01:20:25 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(char **command)
{
	int	n_option;
	int	i;

	n_option = 0;
	i = 1;
	while (command[i] && ft_strncmp(command[i], "-n", 3) == 0)
	{
		n_option = 1;
		i++;
	}
	while (command[i])
	{
		printf("%s", command[i]);
		i++;
	}
	if (!n_option)
		printf("\n");
}