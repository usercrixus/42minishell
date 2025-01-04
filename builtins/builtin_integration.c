/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:57:59 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/04 22:23:29 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_integration(char **command)
{
	if (ft_strncmp(command[0], "exit", ft_strlen("exit") + 1) == 0)
		exit(0);
	return (0);
}