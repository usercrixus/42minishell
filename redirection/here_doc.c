/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:27:35 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/30 22:49:44 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./redirect.h"

int	build_here_doc(t_str *str, char *delimiter)
{
	char	*line;

	line = readline(STDIN_FILENO);
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
	{
		if (!ft_str_push(str, line, ft_strlen(line)))
			return (0);
		free(line);
		if (!ft_str_push(str, "\n", 1))
			return (0);
		line = readline(STDIN_FILENO);
	}
	free(line);
	return (1);
}

int	set_here_doc(char *delimiter)
{
	t_str	*str;
	char	*buff;
	int		tmp_file;

	str = ft_str_create();
	if (!str)
		return (0);
	if (!build_here_doc(str, delimiter))
		return (ft_str_free(str), 0);
	buff = ft_str_get_char_array(str, str->size - str->start);
	if (!buff)
		return (0);
	tmp_file = open(delimiter, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (!tmp_file)
		return (free(buff), ft_str_free(str), 0);
	write(tmp_file, buff, str->size - str->start);
	return (close(tmp_file), free(buff), ft_str_free(str), 1);
}
