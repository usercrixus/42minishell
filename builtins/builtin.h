/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:14:40 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/12 21:34:49 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

int		builtin_main_executer(char **command);
int		builtin_child_executer(char **command);
void	ft_exit(int status);
int		ft_pwd(void);
int		ft_cd(char **command);
int		ft_echo(char **command);
int		ft_unset(char **command);
int		ft_env(char **command);
int		ft_export(char **command);

#endif