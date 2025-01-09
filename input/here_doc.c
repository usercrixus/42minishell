/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:27:35 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/09 04:44:45 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_here_doc(t_str *str, char *delimiter)
{
	char	*line;

	line = readline(">");
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		if (!ft_str_push(str, line, ft_strlen(line)))
			return (0);
		free(line);
		if (!ft_str_push(str, "\n", 1))
			return (0);
		line = readline(">");
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
	tmp_file = open("here_doc", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (!tmp_file)
		return (free(buff), ft_str_free(str), 0);
	write(tmp_file, buff, str->size - str->start);
	return (close(tmp_file), free(buff), ft_str_free(str), 1);
}

int	get_here_doc(char *delimiter)
{
	int	fd_in;

	if (!set_here_doc(delimiter))
		return (0);
	fd_in = open("here_doc", O_RDONLY);
	if (fd_in == -1)
	{
		perror(delimiter);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			return (perror("Failed to open /dev/null"), 0);
	}
	if (unlink("here_doc") == -1)
		return (close(fd_in), 0);
	return (fd_in);
}
