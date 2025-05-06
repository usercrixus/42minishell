/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:08:21 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/11 17:17:44 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *block, int c, size_t size)
{
	unsigned char	*byte_memory_block;
	size_t			i;

	byte_memory_block = (unsigned char *) block;
	i = 0;
	while (i < size)
	{
		if (byte_memory_block[i] == (unsigned char)c)
			return ((void *)(block + i));
		i++;
	}
	return (0);
}
