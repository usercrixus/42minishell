/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:45 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/07 07:55:25 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "./../ft_str/ft_str.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char				*get_next_line(int fd);
unsigned long long	is_line_feed(t_str *str);

#endif