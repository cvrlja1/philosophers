/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:19:30 by mbonengl          #+#    #+#             */
/*   Updated: 2024/12/09 15:39:11 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	checkoverflow(int res, int num, int sign)
{
	if (sign == 1)
	{
		if (res > (INT_MAX - num) / 10)
			return (-1);
	}
	else
	{
		if (-res < (INT_MIN + num) / 10)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	res;
	int		of;

	res = 0;
	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9' && *nptr)
	{
		of = checkoverflow(res, *nptr - '0', sign);
		if (of != 1)
			return (of);
		res = res * 10 + *nptr - 48;
		nptr++;
	}
	return ((int)res * sign);
}
