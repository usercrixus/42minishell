/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:59:38 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 18:18:17 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "../42libft/ft_base/libft.h"

/**
 * check if there is a syntax error in the command
 * return : 1 if a syntax error is found, 0 if not
 */
int		is_syntax_error(char *command);
/**
 * shift (on the left) by 2 an array of char* (char **), freeing
 * the first 2 elements.
 * command : the command to shift
 */
void	shift(char **command);

#endif