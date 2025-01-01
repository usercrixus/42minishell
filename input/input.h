/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:14:11 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/31 21:14:16 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../42libft/ft_base/libft.h"
# include "commands_array.h"
# include "input_array.h"
# include "output_array.h"

typedef struct s_command_data
{
	char	***commands_array;
	int		*input_array;
	int		*output_array;
}	t_command_data;

extern char	**environ;
/**
 * Infinite loop reading stdin.
 * 
 * return : 0 for error.
 */
int			input_loop(void);
/**
 * find the path corresponding to the command. If not found, return the command.
 * 
 * return : command pathed, if not found, command. 0 for error.
 */
char		*pathed_command(char *command);

#endif
