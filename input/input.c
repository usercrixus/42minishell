/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:05:42 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/30 15:07:15 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./input.h"
#include "../pipeline/pipeline.h"

int	manage_line(char *line)
{
	char	**commands;
	int		i;

	commands = ft_split(line, '|');
	if (!commands)
		return (0);
	i = 0;
	while (commands[i])
		i++;
	launch_pipe_series(commands, i - 1, i - 1);
	while (i-- > 0)
		waitpid(-1, NULL, 0);
	ft_free_split(commands);
	return (1);
}

int	input_loop(void)
{
	char	*line;
	int		stdin_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	while (1)
	{
		printf("> ");
		line = readline(STDIN_FILENO);
		if (!line)
			return (0);
		manage_line(line);
		free(line);
		dup2(stdin_cpy, STDIN_FILENO);
	}
	return (1);
}
