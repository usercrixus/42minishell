/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:55:39 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 12:30:11 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_directory(char **command)
{
	printf("chdir: error retrieving current directory: getcwd:");
	printf(" cannot access parent directories: No such file or directory\n");
	chdir(command[1]);
}

int	create_cmd(char *cmd, char *final_cmd, char **home, char **command)
{
	cmd = ft_substr(command[1], 1, ft_strlen(command[1]));
	if (!cmd)
		return (1);
	final_cmd = ft_strjoin(home[1], cmd);
	if (!final_cmd)
		return (free(cmd), 1);
	if (chdir(final_cmd) == -1)
	{
		free(final_cmd);
		free(cmd);
		return (1);
	}
	free(final_cmd);
	free(cmd);
	return (0);
}
