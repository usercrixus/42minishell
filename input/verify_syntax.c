/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 01:52:48 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 01:11:18 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	oi_syntax_helper(char *command)
{
	if (!*command)
	{
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
		return (1);
	}
	else if (ft_strncmp(command, "<<", 2) == 0)
		return (ft_putstr_fd(
				"syntax error near unexpected token '<<'\n", 2), 1);
	else if (ft_strncmp(command, "<", 1) == 0)
		return (ft_putstr_fd("syntax error near unexpected token '<'\n", 2), 1);
	else if (ft_strncmp(command, ">>", 2) == 0)
		return (ft_putstr_fd(
				"syntax error near unexpected token '>>'\n", 2), 1);
	else if (ft_strncmp(command, ">", 1) == 0)
		return (ft_putstr_fd("syntax error near unexpected token '>'\n", 2), 1);
	else if (ft_strncmp(command, "|", 1) == 0)
		return (ft_putstr_fd("syntax error near unexpected token '|'\n", 2), 1);
	return (0);
}

int	pipe_syntax_helper(char *command)
{
	if (!*command)
	{
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
		return (1);
	}
	else if (ft_strncmp(command, "|", 1) == 0)
		return (ft_putstr_fd("syntax error near unexpected token '|'\n", 2), 1);
	return (0);
}

int	is_io_syntax_error(char *command)
{
	if (ft_strncmp(command, "<<", 2) == 0
		|| ft_strncmp(command, "<", 1) == 0)
	{
		if (ft_strncmp(command, "<<", 2) == 0)
			command += 2;
		else
			command++;
		while (*command == ' ')
			command++;
		if (oi_syntax_helper(command))
			return (1);
	}
	else if (ft_strncmp(command, ">>", 2) == 0
		|| ft_strncmp(command, ">", 1) == 0)
	{
		if (ft_strncmp(command, ">>", 2) == 0)
			command += 2;
		else
			command++;
		while (*command == ' ')
			command++;
		if (oi_syntax_helper(command))
			return (1);
	}
	return (0);
}

int	is_pipe_syntax_error(char *command)
{
	if (ft_strncmp(command, "|", 1) == 0)
	{
		command++;
		while (*command == ' ')
			command++;
		if (pipe_syntax_helper(command))
			return (1);
	}
	return (0);
}

int	is_syntax_error(char *command)
{
	char	quote;

	quote = 0;
	while (*command)
	{
		if (*command == '\'' || *command == '"')
		{
			if (*command == quote)
				quote = 0;
			else if (get_char_occurence(command, *command) > 1)
				quote = *command;
		}
		if (!quote)
		{
			if (is_io_syntax_error(command) || is_pipe_syntax_error(command))
				return (1);
		}
		command++;
	}
	return (0);
}
