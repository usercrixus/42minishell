/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_array.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:00:44 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/31 21:01:15 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ARRAY_H
# define INPUT_ARRAY_H

# include "here_doc.h"
# include <fcntl.h>
# include "../42libft/ft_base/libft.h"
# include "./commands_array.h"
# include "utils.h"

int	*get_input_array(char ***commands_array);

#endif