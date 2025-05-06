/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:54:45 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/14 17:44:20 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag_error(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int	flag(char **command)
{
	int	i;
	int	j;

	i = 1;
	while (command[i][0] == '-' && strlen(command[i]) > 1)
	{
		j = 1;
		while (command[i][j])
		{
			if (is_flag_error(command[i][j], "n"))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_echo(char **command)
{
	int	n_option;
	int	i;

	if (!command[1])
		return (0);
	n_option = 0;
	i = flag(command);
	n_option = i - 1;
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
	return (0);
}
