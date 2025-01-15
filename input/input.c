/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:05:42 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/15 00:13:45 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	destroy_all(t_command_data *cmds_data)
{
	if (cmds_data->input_array != 0)
	{
		free(cmds_data->input_array);
		cmds_data->input_array = 0;
	}
	if (cmds_data->output_array != 0)
	{
		free(cmds_data->output_array);
		cmds_data->output_array = 0;
	}
	if (cmds_data->commands_array != 0)
		destroy_commands_array(cmds_data->commands_array);
}

int	launch_line(t_command_data *cmds_data)
{
	int	cmds_size;
	int	status_code;

	cmds_size = get_triple_array_size(cmds_data->commands_array);
	if (cmds_size == 1)
	{
		status_code = builtin_main_executer(cmds_data->commands_array[0]);
		if (status_code != 127)
		{
			if (status_code == -1)
				return (EXIT);
			export_errno(status_code);
			return (SUCCESS);
		}
	}
	if (!launch_pipe_series(cmds_data, cmds_size))
		return (ERROR);
	return (NONE);
}

int	set_data(t_command_data	*cmds_data, char *line)
{
	char	*spaced_line;

	spaced_line = get_reconstruct_space(line);
	if (!spaced_line)
		return (0);
	cmds_data->commands_array = get_commands_array(spaced_line);
	free(spaced_line);
	if (!cmds_data->commands_array)
		return (0);
	if (!reconstruct_env_var(cmds_data->commands_array))
		return (0);
	if (!reconstruct_quote(cmds_data->commands_array))
		return (0);
	cmds_data->input_array = get_input_array(cmds_data->commands_array);
	cmds_data->output_array = get_output_array(cmds_data->commands_array);
	if (!cmds_data->input_array || !cmds_data->output_array)
		return (0);
	if (!set_pipe_array(cmds_data))
		return (0);
	return (1);
}

enum e_status	manage_line(char *line)
{
	t_command_data	cmds_data;
	enum e_status	status_code;

	cmds_data.commands_array = 0;
	cmds_data.input_array = 0;
	cmds_data.output_array = 0;
	status_code = set_data(&cmds_data, line);
	if (status_code == 0)
		return (destroy_all(&cmds_data), ERROR);
	status_code = launch_line(&cmds_data);
	return (destroy_all(&cmds_data), status_code);
}

void	input_loop(void)
{
	char			*line;
	enum e_status	status;

	status = NONE;
	while (status != EXIT)
	{
		g_command_running = -1;
		setup_signal();
		line = readline("\033[1;32mminishell@chodel: \033[0m");
		if (!line)
			exit(atoi(ft_get_env("?")));
		if (line && get_char_occurence(line, ' ') != ft_strlen(line))
		{
			add_history(line);
			if (!is_syntax_error(line))
			{
				g_command_running = 1;
				setup_signal();
				status = manage_line(line);
				if (status == ERROR)
					export_errno(errno);
			}
		}
		free(line);
	}
}
