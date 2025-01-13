/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:27:35 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 20:53:18 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_here_doc_helper(t_str *str, char *line, t_str *buffer)
{
	line = ft_str_get_char_array(buffer, buffer->size);
	if (!line)
		return (free(line), ft_str_free(buffer), 0);
	if (!ft_str_push(str, line, ft_strlen(line))
		|| !ft_str_push(str, "\n", 1))
		return (free(line), ft_str_free(buffer), 0);
	free(line);
	ft_str_free(buffer);
	return (1);
}

int	build_here_doc(t_str *str, char *delimiter)
{
	char	*line;
	t_str	*buffer;

	buffer = 0;
	line = readline(">");
	while (line > 0
		&& ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		if (!reconstruct_arg_env_var(line, &buffer))
			return (free(line), 0);
		free(line);
		if (buffer)
		{
			if (!build_here_doc_helper(str, line, buffer))
				return (0);
			buffer = 0;
		}
		line = readline(">");
	}
	return (free(line), 1);
}

int	set_here_doc(char *delimiter)
{
	t_str	*str;
	char	*buff;
	int		tmp_file;
	int		build_status;

	str = ft_str_create();
	if (!str)
		return (0);
	build_status = build_here_doc(str, delimiter);
	if (!build_status)
		return (ft_str_free(str), 0);
	if (build_status == EOF)
		return (ft_str_free(str), EOF);
	buff = ft_str_get_char_array(str, str->size - str->start);
	if (!buff)
		return (ft_str_free(str), 0);
	tmp_file = open("here_doc", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (!tmp_file)
		return (free(buff), ft_str_free(str), 0);
	write(tmp_file, buff, str->size - str->start);
	return (close(tmp_file), free(buff), ft_str_free(str), 1);
}

int	get_here_doc(char *delimiter)
{
	int	fd_in;
	int	set_status;

	set_status = set_here_doc(delimiter);
	if (!set_status)
		return (0);
	if (set_status == EOF)
		return (printf("bash: warning: here-document at line 1 delimited \
		by end-of-file (wanted '%s')", delimiter), 0);
	fd_in = open("here_doc", O_RDONLY);
	if (fd_in == -1)
	{
		perror(delimiter);
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			return (perror("Failed to open /dev/null"), 0);
	}
	if (unlink("here_doc") == -1)
		return (perror("heredoc unlink error:"), close(fd_in), 0);
	return (fd_in);
}
