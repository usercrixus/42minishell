/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:30:18 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 13:49:36 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	buff[50];
	char	*pwd;

	pwd = getcwd(buff, 50);
	if (pwd == NULL)
	{
		printf("pwd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: No such file or directory\n");
	}
	else
		printf("%s\n", pwd);
	return (0);
}
