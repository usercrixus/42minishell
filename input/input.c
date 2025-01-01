/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:05:42 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/01 01:10:49 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./input.h"
#include "../pipeline/pipeline.h"

int	manage_line(char *line)
{
	int				commands_size;
	t_command_data	commands_data;

	commands_data.commands_array = get_commands_array(line);
	commands_data.input_array = get_input_array(commands_data.commands_array);
	commands_data.output_array = get_output_array(commands_data.commands_array);
	commands_size = get_command_array_size(commands_data.commands_array);
	launch_pipe_series(&commands_data, commands_size - 1, commands_size - 1);
	while (commands_size-- > 0)
		waitpid(-1, NULL, 0);
	free(commands_data.input_array);
	free(commands_data.output_array);
	destroy_commands_array(commands_data.commands_array);
	return (1);
}

int	input_loop(void)
{
	char	*line;

	while (1)
	{
		printf("> ");
		line = readline(STDIN_FILENO);
		if (!line)
			return (0);
		manage_line(line);
		free(line);
	}
	return (1);
}
