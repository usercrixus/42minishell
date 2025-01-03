/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:37:10 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/03 20:29:07 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_var(char *s, char terminator)
{
	t_str	*str;
	int		i;
	char	*var_name;
	int		len_var_name;

	str = ft_str_create();
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != terminator)
		i++;
	ft_str_push(str, s, i);
	ft_str_push(str, "=", 1);
	var_name = ft_str_get_char_array(str, str->size);
	len_var_name = ft_strlen(var_name);
	ft_str_free(str);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, strlen(var_name)) == 0)
			return (&environ[i][len_var_name]);
		i++;
	}
	return (0);
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

int	manage_reconstruct_quote(char **commands)
{
	int		i;
	int		j;
	char	quote;
	t_str 	*buffer;
	char	*env_var;

	quote = 0;
	i = 0;
	while (commands[i])
	{
		j = 0;
		buffer = ft_str_create();
		while (commands[i][j])
		{
			if (!quote && (commands[i][j] == '\'' || commands[i][j] == '"'))
			{
				quote = commands[i][j];
				j++;
			}
			else if (commands[i][j] == quote)
			{
				quote = 0;
				j++;
			}
			else
			{
				if (quote != '\'' && commands[i][j] == '$')
				{
					j++;
					env_var = get_env_var(&commands[i][j], quote);
					ft_str_push(buffer, env_var, ft_strlen(env_var));
					//while (commands[i][j] && commands[i][j] != ' ' && (quote && commands[i][j] != quote))
					j++;
				}
				else
				{
					ft_str_push(buffer, &commands[i][j], 1);
					j++;
				}
			}
		}
		free(commands[i]);
		commands[i] = ft_str_get_char_array(buffer, buffer->size);
		ft_str_free(buffer);
		i++;
	}
	return (1);
}

int	reconstruct_quote(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		manage_reconstruct_quote(commands[i]);
		i++;
	}
	return (1);
}