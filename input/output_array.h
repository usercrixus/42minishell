/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:34:09 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 18:15:34 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_ARRAY_H
# define OUTPUT_ARRAY_H

# include <fcntl.h>
# include "../42libft/ft_base/libft.h"
# include "./commands_array.h"
# include <sys/stat.h>
# include "utils.h"

/**
 * commands_array : the pointer commands_array
 * return : Array of fd. Each fd is on the rank of the command (example : 
 * value[0] represent the fd representing the output redirection of
 * the first command, 0 if no redirection)
 */
int	*get_output_array(char ***commands_array);

#endif