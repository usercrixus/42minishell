/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:57:42 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/30 16:25:32 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <unistd.h>
# include "../42libft/ft_base/libft.h"
# include "../input/input.h"
# include "../redirection/redirect.h"

extern char	**environ;

/**
 * launch a series of command separated by a pipe.
 * Typicaly, split on pipe '|' character
 * 
 * argv : array of commands string
 * limit : number of command -1 (typicaly the split size -1)
 * max : same as limit
 */
int			launch_pipe_series(char **argv, int limit, int max);

#endif