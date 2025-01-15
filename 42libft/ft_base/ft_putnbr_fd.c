/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:23:04 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/14 15:59:47 by achaisne         ###   ########.fr       */
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

int	ft_putnbr_fd(int n, int fd)
{
	int		size;
	int		i;

	size = get_size(n);
	i = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		i++;
		ft_putchar_fd(((n / power10(size - i - 1)) * -1 % 10) + '0', fd);
		n += power10(size - i - 1) * ((n / power10(size - i - 1) * -1));
		n *= -1;
		i++;
	}
	while (i < size)
	{
		ft_putchar_fd(((n / power10(size - i - 1)) % 10) + '0', fd);
		i++;
	}
	return (i);
}
