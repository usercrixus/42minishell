/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:07:23 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/11 20:34:25 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t element_count, size_t element_size)
{
	void	*block;
	size_t	size;

	if (element_count != 0
		&& element_size > (unsigned long)4294967295 / element_count
	)
		return (0);
	size = element_size * element_count;
	block = (void *)malloc(size);
	if (!block)
		return (0);
	ft_bzero(block, size);
	return (block);
}
