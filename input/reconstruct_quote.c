/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:37:10 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/05 02:19:07 by achaisne         ###   ########.fr       */
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
	while (s[i] && s[i] != ' ' && s[i] != terminator)
		i++;
	if (!ft_str_push(str, s, i))
		return (0);
	var_name = ft_str_get_char_array(str, str->size);
	if (!var_name)
		return (ft_str_free(str), (char *)0);
	var_value = getenv(var_name);
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

	if (quote != '\'' && command[*j] == '$')
	{
		(*j)++;
		env_var = get_env_var(&command[*j], quote);
		if (!env_var || !ft_str_push(buffer, env_var, ft_strlen(env_var)))
			return (0);
		while (command[*j]
			&& command[*j] != ' ' && command[*j] != quote)
			(*j)++;
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
