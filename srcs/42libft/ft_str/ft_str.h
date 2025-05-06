/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:45 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 04:33:50 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_H
# define FT_STR_H

# include <stdlib.h>
# include <unistd.h>
# include "../ft_base/libft.h"

# define T_STR_BUFFER_SIZE 1024

typedef struct s_char_list
{
	char				c[T_STR_BUFFER_SIZE];
	struct s_char_list	*next;
}	t_char_list;

typedef struct s_str
{
	unsigned long long	size;
	int					start;
	t_char_list			*head;
	t_char_list			*tail;
}	t_str;

t_str	*ft_str_create(void);
void	ft_str_free(t_str *str);
int		ft_str_push(t_str *str, char *c, ssize_t len);
char	*ft_str_get_char_array(t_str *str, unsigned long long line_size);
int		ft_str_troncate_begin(t_str *str, unsigned long long size);

#endif