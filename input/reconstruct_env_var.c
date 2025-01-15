/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_env_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:33:47 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/14 16:27:02 by achaisne         ###   ########.fr       */
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
	while (s[i] && s[i] != terminator
		&& (s[i] == '?' || s[i] == '_' || ft_isalpha(s[i])))
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

int	push_env(t_str **buffer, char *command, char quote)
{
	char	*env_var;

	env_var = get_env_var(command, quote);
	if (env_var)
	{
		if (!initialize_buffer(buffer))
			return (0);
		if (!ft_str_push(*buffer, env_var, ft_strlen(env_var)))
			return (ft_str_free(*buffer), 0);
	}
	return (1);
}

int	reconstruct_arg_env_var(char *commands, t_str **buffer)
{
	int		j;
	char	quote;

	quote = 0;
	j = 0;
	while (commands[j])
	{
		if (set_quote(&quote, &commands[j]) && !initialize_buffer(buffer))
			return (0);
		if (quote != '\'' && commands[j] == '$'
			&& commands[j + 1] && commands[j + 1] != quote)
		{
			push_env(buffer, &commands[j + 1], quote);
			j++;
			while (commands[j] && commands[j] != quote && (commands[j] == '?'
					|| commands[j] == '_' || ft_isalpha(commands[j])))
				j++;
		}
		else if (!push_char(buffer, &commands[j++]))
			return (0);
	}
	return (1);
}

int	reconstruct_command_env_var(char **commands)
{
	int		i;
	t_str	*buffer;

	i = 0;
	buffer = 0;
	while (commands[i])
	{
		if (!reconstruct_arg_env_var(commands[i], &buffer))
			return (0);
		if (!set_command_arg(commands, buffer, i))
			return (0);
		buffer = 0;
		i++;
	}
	return (1);
}

int	reconstruct_env_var(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (!reconstruct_command_env_var(commands[i]))
			return (0);
		i++;
	}
	return (1);
}
