/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:26:49 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/08 21:09:17 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	*byte_destination;
	unsigned char	*byte_source;
	size_t			i;

	byte_destination = (unsigned char *) destination;
	byte_source = (unsigned char *) source;
	if (source < destination)
	{
		while (size > 0)
		{
			size--;
			byte_destination[size] = byte_source[size];
		}
	}
	else
	{
		i = 0;
		while (i < size)
		{
			byte_destination[i] = byte_source[i];
			i++;
		}
	}
	return (destination);
}
