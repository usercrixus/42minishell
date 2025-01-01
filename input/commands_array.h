/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_array.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:55 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 18:11:39 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_ARRAY_H
# define COMMANDS_ARRAY_H

# include "../42libft/ft_base/libft.h"

/**
 * line : the line returned by readline (input of the terminal)
 * return : an array of char** (array of split), null terminated
 */
char	***get_commands_array(char *line);
/**
 * destroy (free) the commands array var.
 * commands_array : the pointer commands_array
 */
void	destroy_commands_array(char ***commands_array);
/**
 * commands_array : the pointer commands_array
 * return : the size of the command array
 */
int		get_command_array_size(char ***commands_array);

#endif