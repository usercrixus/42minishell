/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorel <gmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:14:40 by gmorel            #+#    #+#             */
/*   Updated: 2025/01/07 11:28:26 by gmorel           ###   ########.fr       */
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
# include <errno.h>     // For errno and ECHILD
# include <sys/types.h> // For pid_t

# include "./42libft/ft_printf/ft_printf.h"
# include "./42libft/ft_base/libft.h"
# include "./42libft/ft_str/ft_str.h"

typedef struct s_command_data
{
	char	***commands_array;
	int		*input_array;
	int		*output_array;
}	t_command_data;

extern char						**mini_env;
extern volatile sig_atomic_t	g_command_running;

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
 * path and launch the command (with execve)
 * command : the command to execute
 */
int		execute_child(char **command);
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
 * check if there is a syntax error in the command
 * return : 1 if a syntax error is found, 0 if not
 */
int		is_syntax_error(char *command);
/**
 * shift (on the left) by 2 an array of char* (char **), freeing
 * the first 2 elements.
 * command : the command to shift
 * len : the size of shift
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
int		input_loop(void);
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
 * commands_array : the pointer commands_array
 * return : the size of the command array
 */
int		get_command_array_size(char ***commands_array);
/**
 * manage the quote of the command, interpreting with double quote and
 * not with single quote.
 * commands : the command to reconstruct
 */
int		reconstruct_quote(char ***commands);
void	reset_quote(char *quote, int *j);
void	set_quote(char *quote, int *j, char c);
int		set_command(char **commands, t_str *buffer, int i);
/**
 * Split the command, but deactivate the split when a quote (single or double)
 * is found
 * s : the command string
 * c : the character to split on (here typicaly a space or a pipe)
 */
char	**special_split(char const *s, char c);
void	set_end(char const *s, char *is_active, int *i, char c);
int		set_start(char const *s, char *is_active, int *i, char c);
/**
 * Try to launch a command corresponding to command[0]
 * command : the command to launch
 */
int		builtin_integration(char **command);
void	ft_pwd();
void	ft_cd(char **command);
void	ft_echo(char **command);
void	ft_unset(char **command);
void	ft_env(char **command);
void	ft_export(char **command);

void	setup_signals(void);

#endif