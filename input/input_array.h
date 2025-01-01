/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:00:44 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 18:15:30 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ARRAY_H
# define INPUT_ARRAY_H

# include "here_doc.h"
# include <fcntl.h>
# include "../42libft/ft_base/libft.h"
# include "./commands_array.h"
# include "utils.h"

/**
 * commands_array : the pointer commands_array
 * return : Array of fd. Each fd is on the rank of the command (example : 
 * value[0] represent the fd representing the input redirection of
 * the first command, 0 if no redirection)
 */
int	*get_input_array(char ***commands_array);

#endif