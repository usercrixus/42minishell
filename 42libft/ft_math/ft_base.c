/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:00:59 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/01 18:16:03 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

int	ft_abs(int x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

int	ft_ceil(double x)
{
	int	result;

	result = (int)x;
	if ((double)result < x)
		return (result + 1);
	return (result);
}

int	ft_diff(int a, int b)
{
	return (a - b);
}
