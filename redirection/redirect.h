/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:19:25 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/30 23:56:49 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "../42libft/ft_str/ft_str.h"
# include "../42libft/ft_base/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int		redirect(char **command);
int		set_here_doc(char *delimiter);
void	clean_command(char **command, int status);

#endif