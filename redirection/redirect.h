/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:19:25 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/30 16:11:37 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "../42libft/ft_base/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>

int	redirect(char **command);

#endif