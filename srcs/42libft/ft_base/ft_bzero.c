/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:38:35 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/08 20:36:08 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	ft_bzero(void *ptr, size_t size)
{
	size_t			i;
	unsigned char	*byte_ptr;

	i = 0;
	byte_ptr = (unsigned char *)ptr;
	while (i < size)
	{
		byte_ptr[i] = 0;
		i++;
	}
}
