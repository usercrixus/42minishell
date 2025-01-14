/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:14:40 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/14 18:10:28 by gmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/types.h>

# include "./42libft/ft_printf/ft_printf.h"
# include "./42libft/ft_base/libft.h"
# include "./42libft/ft_str/ft_str.h"

# include "./builtins/builtin.h"

typedef struct s_command_data
{
	char	***commands_array;
	int		*input_array;
	int		*output_array;
}	t_command_data;

typedef enum e_status
{
	NONE,
	SUCCESS,
	EXIT,
	MEMORY_ERROR
}	t_status;

extern char						**g_mini_env;
extern pid_t					g_command_running;

void	export_errno(int code_error);
char	*ft_get_env(const char *var_name);
/**
 * launch a series of command separated by a pipe.
 * Typicaly, split on pipe '|' character
 * 
 * command_data : the t_command_data object
 * max : number of command (typicaly the split size)
 * return : the pid of the last command of the pipe
 */
int		launch_pipe_series(t_command_data *command_data, int max);
/**
 * close all element of fds (fd array)
 * fds : array of fd
 * size : the size of fds
 */
void	close_fds(int *fds, int size);
/**
 * find the path corresponding to the command. If not found, return the command.
 * 
 * return : command pathed, if not found, command. 0 for error.
 */
char	*get_pathed_command(char *command);
/**
 * 
 */
int		is_syntax_error(char *command);
/**
 * shift (on the left) by size an array of char* (char **), freeing
 * the first size elements.
 * command : the command to shiftSIG_IGN
 */
void	shift(char **command, int size);
/**
 * commands_array : the pointer commands_array
 * return : Array of fd. Each fd is on the rank of the command (example : 
 * value[0] represent the fd representing the output redirection of
 * the first command, 0 if no redirection)
 */
int		*get_output_array(char ***commands_array);
/**
 * Infinite loop reading stdin.
 * 
 * return : 0 for error.
 */
void	input_loop(void);
/**
 * create a file with the content set by the stdinput open by heredoc
 * 
 * delimiter : the here_doc delimiter
 * return : the file descriptor pointing in the file created by here_doc
 */
int		get_here_doc(char *delimiter);
/**
 * commands_array : the pointer commands_array
 * return : Array of fd. Each fd is on the rank of the command (example : 
 * value[0] represent the fd representing the input redirection of
 * the first command, 0 if no redirection)
 */
int		*get_input_array(char ***commands_array);
/**
 * line : the line returned by readline (input of the terminal)
 * return : an array of char** (array of split), null terminated
 */
char	***get_commands_array(char *line);
/**
 * set the input and output array with pipe for all commands that have
 * no redirection.
 * commands_data : the t_comma,d_data object
 */
int		set_pipe_array(t_command_data *commands_data);
/**
 * destroy (free) the commands array var.
 * commands_array : the pointer commands_array
 */
void	destroy_commands_array(char ***commands_array);
/**
 * destroy all what is in t_command_data data structure
 * commands_data : the data structure to destroy
 */
void	destroy_all(t_command_data *commands_data);
/**
 * commands_array : the pointer commands_array
 * return : the size of the command array
 */
int		get_triple_array_size(char ***commands_array);
/**
 * Add space before and after keyword
 * << >> < > easily can add some
 * commands_string : the commands_string to format
 */
char	*get_reconstruct_space(char *commands_string);
int		reconstruct_arg_env_var(char *commands, t_str **buffer);
int		reconstruct_quote(char ***commands);
int		reconstruct_env_var(char ***commands);
int		set_command_arg(char **commands, t_str *buffer, int i);
int		set_quote(char *quote, char *s);
int		push_char(t_str **buffer, char *command);
int		initialize_buffer(t_str **buffer);
int		set_command_arg(char **commands, t_str *buffer, int i);
int		get_char_occurence(char *str, char c);
/**
 * Split the command, but deactivate the split when a quote (single or double)
 * is found
 * s : the command string
 * c : the character to split on (here typicaly a space or a pipe)
 */
char	**special_split(char const *s, char c);
int		is_valid_env_id(char *arg);
void	setup_signal(void);

#endif