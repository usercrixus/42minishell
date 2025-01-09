/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:37:10 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 18:22:46 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char *s, char terminator)
{
	t_str		*str;
	int			i;
	char		*var_name;
	char		*var_value;

	str = ft_str_create();
	i = 0;
	if (s[i] == '*' || s[i] == '@')
		i++;
	else if (ft_isdigit(s[i]))
	{
		while (s[i] && ft_isdigit(s[i]) && s[i] != terminator)
			i++;
	}
	else
	{
		while (s[i] && ft_isalnum(s[i]) && s[i] != terminator)
			i++;
	}
	if (!ft_str_push(str, s, i))
		return (0);
	var_name = ft_str_get_char_array(str, str->size);
	if (!var_name)
		return (ft_str_free(str), (char *)0);
	var_value = ft_get_env(var_name);
	free(var_name);
	ft_str_free(str);
	return (var_value);
}

int	get_char_occurence(char *str, char c)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			result++;
		i++;
	}
	return (result);
}

int	push_buffer(char *command, char quote, t_str *buffer, int *j)
{
	char	*env_var;
	char	*command_pathed;

	if (quote != '\'' && command[*j] == '=')
	{
		(*j)++;
		command_pathed = get_pathed_command(&command[*j]);
		if (!command_pathed)
			return (0);
		if (access(command_pathed, F_OK) == -1)
		{
			if (!ft_str_push(buffer, command_pathed, ft_strlen(command_pathed)))
				return (0);
			if (!ft_str_push(buffer, " not found", ft_strlen(" not found")))
				return (0);
		}
		else
			if (!ft_str_push(buffer, command_pathed, ft_strlen(command_pathed)))
				return (0);
		while (command[*j])
			(*j)++;
		// if (command_pathed != &command[*j])
		// 	free(command_pathed);
	}
	else if (quote != '\'' && command[*j] == '$')
	{
		(*j)++;
		while (command[*j] == '=')
			(*j)++;
		env_var = get_env_var(&command[*j], quote);
		if (!env_var)
			env_var = "";
		if (!ft_str_push(buffer, env_var, ft_strlen(env_var)))
			return (0);
		if (command[*j] == '*' || command[*j] == '@')
			(*j)++;
		else if (ft_isdigit(command[*j]))
		{
			while (command[*j] && ft_isdigit(command[*j]))
				(*j)++;
		}
		else
		{
			while (command[*j] && ft_isalnum(command[*j]) && command[*j] != quote)
				(*j)++;
		}
	}
	else
	{
		if (!ft_str_push(buffer, &command[*j], 1))
			return (0);
		(*j)++;
	}
	return (1);
}

int	manage_reconstruct_quote(char **commands, char quote, t_str *buffer)
{
	int		i;
	int		j;

	quote = 0;
	i = 0;
	while (commands[i])
	{
		j = 0;
		buffer = ft_str_create();
		if (!buffer)
			return (0);
		while (commands[i][j])
		{
			if (!quote && (commands[i][j] == '\'' || commands[i][j] == '"')
				&& get_char_occurence(&commands[i][j], commands[i][j]) > 1)
				set_quote(&quote, &j, commands[i][j]);
			else if (commands[i][j] == quote)
				reset_quote(&quote, &j);
			else if (!push_buffer(commands[i], quote, buffer, &j))
				return (0);
		}
		if (!set_command(commands, buffer, i++))
			return (0);
	}
	return (1);
}

int	reconstruct_quote(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (!manage_reconstruct_quote(commands[i], 0, 0))
			return (0);
		i++;
	}
	return (1);
}
