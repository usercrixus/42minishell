/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:27:38 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/05 06:14:17 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char **command)
{
	if (!command[1])
		ft_putstr_fd("cd: bad arguments\n", 2);
	else if (chdir(command[1]) == -1)
		perror(command[1]);
}