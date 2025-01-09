/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:05:42 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 04:25:59 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_data(t_command_data	*commands_data, char *line)
{
	commands_data->commands_array = 0;
	commands_data->input_array = 0;
	commands_data->output_array = 0;
	if (is_syntax_error(line))
		return (SYNTAX_ERROR);
	commands_data->commands_array = get_commands_array(line);
	if (!commands_data->commands_array
		|| !commands_data->commands_array[0])
		return (MEMORY_ERROR);
	if (!reconstruct_quote(commands_data->commands_array)
		|| !commands_data->commands_array[0][0])
		return (MEMORY_ERROR);
	commands_data->input_array = get_input_array(commands_data->commands_array);
	commands_data->output_array
		= get_output_array(commands_data->commands_array);
	if (!commands_data->input_array || !commands_data->output_array)
		return (MEMORY_ERROR);
	if (!set_pipe_array(commands_data))
		return (MEMORY_ERROR);
	return (SUCCESS);
}

void	destroy_all(t_command_data *commands_data)
{
	if (commands_data->input_array != 0)
	{
		free(commands_data->input_array);
		commands_data->input_array = 0;
	}
	if (commands_data->output_array != 0)
	{
		free(commands_data->output_array);
		commands_data->output_array = 0;
	}
	if (commands_data->commands_array != 0)
		destroy_commands_array(commands_data->commands_array);
}

int	manage_line(char *line)
{
	int				commands_size;
	t_command_data	commands_data;
	int				status_code;

	g_command_running = 1;
	status_code = set_data(&commands_data, line);
	if (status_code == MEMORY_ERROR || status_code == SYNTAX_ERROR)
		return (destroy_all(&commands_data), status_code);
	if (!commands_data.commands_array[0][0])
		return (SUCCESS);
	commands_size = get_command_array_size(commands_data.commands_array);
	if (commands_size == 1)
	{
		status_code = builtin_main_executer(&commands_data);
		if (status_code != 127)
		{
			destroy_all(&commands_data);
			export_errno(status_code);
			if (status_code == -1)
				return (EXIT);
			return (SUCCESS);
		}
	}
	launch_pipe_series(&commands_data, commands_size);
	return (destroy_all(&commands_data), SUCCESS);
}

char	*clean_line(char *line)
{
	char	*line_trimmed;

	line_trimmed = ft_strtrim(line, " ");
	if (!line_trimmed)
		return (0);
	free(line);
	return (line_trimmed);
}

void	input_loop(void)
{
	char	*line;
	char	status;

	status = NONE;
	while (status != EXIT)
	{
		g_command_running = 0;
		line = readline("\033[1;32mminishell@chodel: \033[0m");
		if (!line)
			ft_exit(0);
		line = clean_line(line);
		if (line && line[0])
		{
			add_history(line);
			status = manage_line(line);
			if (status == MEMORY_ERROR)
				ft_putstr_fd("Error during the parsing\n", 2);
		}
		free(line);
	}
	ft_exit(0);
}
