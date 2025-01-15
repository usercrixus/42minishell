/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:27:35 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/15 01:00:52 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	push_here_doc_str(t_str *here_doc_str, char *line, t_str *buffer)
{
	line = ft_str_get_char_array(buffer, buffer->size);
	if (!line)
		return (free(line), ft_str_free(buffer), 0);
	if (!ft_str_push(here_doc_str, line, ft_strlen(line))
		|| !ft_str_push(here_doc_str, "\n", 1))
		return (free(line), ft_str_free(buffer), 0);
	free(line);
	ft_str_free(buffer);
	return (1);
}

char	*read_line_helper(char *delimiter)
{
	char	*line;

	line = readline(">");
	if (!line && errno == 0)
	{
		printf("bash: warning: here-document delimited by");
		printf(" end-of-file (wanted '%s')\n", delimiter);
	}
	return (line);
}

int	build_here_doc(t_str *here_doc_str, char *delimiter)
{
	char	*line;
	t_str	*buffer;

	buffer = 0;
	line = read_line_helper(delimiter);
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		if (!reconstruct_arg_env_var(line, &buffer))
			return (free(line), 0);
		if (buffer)
		{
			if (!push_here_doc_str(here_doc_str, line, buffer))
				return (free(line), 0);
			buffer = 0;
		}
		free(line);
		line = read_line_helper(delimiter);
	}
	if (!line && ft_strncmp(ft_get_env("?"), "0", 2) != 0)
		return (0);
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
		return (ft_str_free(str), 0);
	tmp_file = open("here_doc", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (tmp_file == -1)
		return (free(buff), ft_str_free(str), 0);
	write(tmp_file, buff, str->size - str->start);
	return (close(tmp_file), free(buff), ft_str_free(str), 1);
}

int	get_here_doc(char *delimiter)
{
	int	fd_in;

	if (!set_here_doc(delimiter))
		return (-1);
	fd_in = open("here_doc", O_RDONLY);
	if (fd_in == -1)
	{
		perror(delimiter);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			return (perror("Failed to open /dev/null"), -1);
	}
	if (unlink("here_doc") == -1)
		return (perror("heredoc unlink error:"), close(fd_in), -1);
	return (fd_in);
}
