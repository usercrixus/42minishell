/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:34:09 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/31 21:01:25 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_ARRAY_H
# define OUTPUT_ARRAY_H

# include <fcntl.h>
# include "../42libft/ft_base/libft.h"
# include "./commands_array.h"
# include <sys/stat.h>
# include "utils.h"

int	*get_output_array(char ***commands_array);

#endif