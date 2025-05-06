/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:50:14 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/08 21:09:12 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned char	*byte_destination;
	unsigned char	*byte_source;
	size_t			i;

	byte_destination = (unsigned char *) dst;
	byte_source = (unsigned char *) src;
	i = 0;
	while (i < size)
	{
		byte_destination[i] = byte_source[i];
		i++;
	}
	return (dst);
}
