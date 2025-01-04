/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:05:42 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/04 20:16:07 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	manage_line(char *line)
{
	int				commands_size;
	t_command_data	commands_data;

	g_command_running = 1;
	commands_data.commands_array = get_commands_array(line);
	reconstruct_quote(commands_data.commands_array);
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

	setup_signals();
	while (1)
	{
		g_command_running = 0;
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			manage_line(line);
		}
		free(line);
	}
	return (0);
}
