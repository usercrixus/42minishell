/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:05:42 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 01:29:03 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_data(t_command_data	*commands_data, char *line)
{
	commands_data->commands_array = get_commands_array(line);
	if (!commands_data->commands_array
		|| !commands_data->commands_array[0]
		|| !reconstruct_quote(commands_data->commands_array)
		|| !commands_data->commands_array[0][0])
		return (0);
	commands_data->input_array = get_input_array(commands_data->commands_array);
	commands_data->output_array
		= get_output_array(commands_data->commands_array);
	if (!commands_data->input_array || !commands_data->output_array)
		return (0);
	if (!set_pipe_array(commands_data))
		return (0);
	return (1);
}

void	detroy_all(t_command_data *commands_data)
{
	free(commands_data->input_array);
	free(commands_data->output_array);
	destroy_commands_array(commands_data->commands_array);
}

int	manage_line(char *line)
{
	int				commands_size;
	t_command_data	commands_data;
	int				pid;
	int				stat_loc;
	int				errno_code;

	g_command_running = 1;
	if (!set_data(&commands_data, line))
		return (0);
	commands_size = get_command_array_size(commands_data.commands_array);
	if (commands_size == 1)
	{
		errno_code = builtin_main_executer(&commands_data);
		if (errno_code != 127)
			return (detroy_all(&commands_data),
				export_errno(errno_code), errno_code);
	}
	pid = launch_pipe_series(&commands_data, commands_size);
	while (commands_size-- > 0)
	{
		if (waitpid(-1, &stat_loc, 0) == pid && WIFEXITED(stat_loc))
			export_errno(WEXITSTATUS(stat_loc));
	}
	return (detroy_all(&commands_data), 1);
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
	int		status;

	status = 0;
	while (status != -2)
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
			if (!status)
				ft_putstr_fd("Error during the parsing\n", 2);
		}
		free(line);
	}
	ft_exit(0);
}
