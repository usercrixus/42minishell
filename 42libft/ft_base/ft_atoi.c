/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:40:12 by achaisne          #+#    #+#             */
/*   Updated: 2024/11/11 18:42:19 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	is_neg;

	result = 0;
	i = 0;
	is_neg = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_neg = 1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result *= 10;
		if (is_neg)
			result -= str[i] - '0';
		else
			result += str[i] - '0';
		i++;
	}
	return (result);
}
