/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:22:05 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/09 17:58:13 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	unsigned char	*byte_ptr1;
	unsigned char	*byte_ptr2;
	size_t			i;

	byte_ptr1 = (unsigned char *) ptr1;
	byte_ptr2 = (unsigned char *) ptr2;
	i = 0;
	while (i < size)
	{
		if (byte_ptr1[i] != byte_ptr2[i])
			return (byte_ptr1[i] - byte_ptr2[i]);
		i++;
	}
	return (0);
}
