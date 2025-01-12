/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:37:10 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 05:22:28 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char *s, char terminator)
{
	t_str		*var_name_buffer;
	int			i;
	char		*var_name;
	char		*var_value;

	var_name_buffer = ft_str_create();
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '$' && s[i] != terminator)
		i++;
	if (!ft_str_push(var_name_buffer, s, i))
		return (0);
	var_name = ft_str_get_char_array(var_name_buffer, var_name_buffer->size);
	ft_str_free(var_name_buffer);
	if (!var_name)
		return ((char *)0);
	var_value = ft_get_env(var_name);
	free(var_name);
	return (var_value);
}

int	initialize_buffer(t_str **buffer)
{
	if (!*buffer)
	{
		*buffer = ft_str_create();
		if (!*buffer)
			return (0);
	}
	return (1);
}

int	push_buffer(char *command, char quote, t_str **buffer, int *j)
{
	char	*env_var;

	if (quote != '\'' && command[*j] == '$' && command[(*j) + 1] && command[(*j) + 1] != quote)
	{
		env_var = get_env_var(&command[++(*j)], quote);
		if (env_var)
		{
			if (!initialize_buffer(buffer))
				return (0);
			if (!ft_str_push(*buffer, env_var, ft_strlen(env_var)))
				return (ft_str_free(*buffer), 0);
		}
		while (command[*j] && command[*j] != '$'
			&& command[*j] != ' ' && command[*j] != quote)
			(*j)++;
	}
	else
	{
		if (!initialize_buffer(buffer))
			return (0);
		if (!ft_str_push(*buffer, &command[*j], 1))
			return (ft_str_free(*buffer), 0);
		(*j)++;
	}
	return (1);
}

int	manage_reconstruct_quote(char **commands, char quote, t_str *buffer)
{
	int		i;
	int		j;

	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			if (!quote && (commands[i][j] == '\'' || commands[i][j] == '"')
				&& get_char_occurence(&commands[i][j], commands[i][j]) > 1)
			{
				if (!initialize_buffer(&buffer))
					return (0);
				set_quote(&quote, &j, commands[i][j]);
			}
			else if (commands[i][j] == quote)
				reset_quote(&quote, &j);
			else if (!push_buffer(commands[i], quote, &buffer, &j))
				return (0);
		}
		if (!set_command(commands, &buffer, i++))
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
		if (!commands[i][0])
		{
			commands[i][0] = ft_strdup("true");
			if (!commands[i][0])
				return (0);
		}
		i++;
	}
	return (1);
}
