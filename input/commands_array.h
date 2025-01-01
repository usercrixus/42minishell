/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_array.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:55 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/31 14:46:54 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_ARRAY_H
# define COMMANDS_ARRAY_H

# include "../42libft/ft_base/libft.h"

char	***get_commands_array(char *line);
void	destroy_commands_array(char ***commands_array);
int		get_command_array_size(char ***commands_array);

#endif