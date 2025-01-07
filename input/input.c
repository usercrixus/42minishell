/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:05:42 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/07 18:33:16 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_data(t_command_data	*commands_data, char *line)
{
	commands_data->commands_array = get_commands_array(line);
	if (!commands_data->commands_array
		|| !reconstruct_quote(commands_data->commands_array))
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

int	execute_parent_commands(t_command_data	*commands_data)
{
	if (ft_strncmp(commands_data->commands_array[0][0], "exit", 5) == 0)
		exit(0);
	if (ft_strncmp(commands_data->commands_array[0][0], "env", 4) == 0)
		return (ft_env(commands_data->commands_array[0]), 1);
	if (ft_strncmp(commands_data->commands_array[0][0], "export", 7) == 0)
		return (ft_export(commands_data->commands_array[0]), 1);
	if (ft_strncmp(commands_data->commands_array[0][0], "unset", 6) == 0)
		return (ft_unset(commands_data->commands_array[0]), 1);
	if (ft_strncmp(commands_data->commands_array[0][0], "cd", 3) == 0)
		return (ft_cd(commands_data->commands_array[0]), 1);
	return (0);
}

int	manage_line(char *line)
{
	int				commands_size;
	t_command_data	commands_data;
	int				pid;
	int				stat_loc;

	g_command_running = 1;
	if (!set_data(&commands_data, line))
		return (0);
	commands_size = get_command_array_size(commands_data.commands_array);
	if (commands_size == 1 && execute_parent_commands(&commands_data))
	{
		export_errno(execute_parent_commands(&commands_data));
		return (1);
	}
	pid = launch_pipe_series(&commands_data, commands_size);
	while (commands_size-- > 0)
	{
		if (waitpid(-1, &stat_loc, 0) == pid && WIFEXITED(stat_loc))
			export_errno(WEXITSTATUS(stat_loc));
	}
	free(commands_data.input_array);
	free(commands_data.output_array);
	destroy_commands_array(commands_data.commands_array);
	return (1);
}

int	input_loop(void)
{
	char	*line;
	char	buff[50];

	setup_signals();
	while (1)
	{
		g_command_running = 0;
		printf("\033[1;32mminishell@chodel\033[0m:\033[1;34m%s",
			getcwd(buff, 50));
		line = readline("\033[0m$ \033[0m");
		if (!line)
			return (1);
		if (*line)
		{
			add_history(line);
			if (!manage_line(line))
				ft_putstr_fd("Error during the parsing", 2);
		}
		free(line);
	}
	return (1);
}
