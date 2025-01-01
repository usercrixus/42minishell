/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:59:17 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/31 21:43:06 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include <fcntl.h>
# include <sys/stat.h>
# include "../42libft/ft_str/ft_str.h"
# include "../42libft/ft_base/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/**
 * create a file with the content set by the stdinput open by heredoc
 * 
 * delimiter : the here_doc delimiter
 * return : the file descriptor pointing in the file created by here_doc
 */
int	get_here_doc(char *delimiter);

#endif