/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:36:16 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/08 21:08:52 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static int	power10(int n)
{
	int	result;

	result = 1;
	while (n)
	{
		result *= 10;
		n--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	int		i;

	size = get_size(n);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (0);
	i = 0;
	if (n < 0)
	{
		result[i] = '-';
		i++;
		result[i] = ((n / power10(size - i - 1)) * -1 % 10) + '0';
		n += power10(size - i - 1) * ((n / power10(size - i - 1) * -1));
		n *= -1;
		i++;
	}
	while (i < size)
	{
		result[i] = ((n / power10(size - i - 1)) % 10) + '0';
		i++;
	}
	result[i] = '\0';
	return (result);
}
