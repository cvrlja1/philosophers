/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:14:48 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/12/30 23:32:18 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_time_micro(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_error(T_ERR), -1);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

int	ft_usleep(long milliseconds, t_philo *philo)
{
	unsigned long	end_t;
	unsigned long	rem_t;

	end_t = current_time_micro() + (milliseconds * 1000);
	while (current_time_micro() < end_t)
	{
		if (is_dead(philo))
			return (1);
		rem_t = end_t - current_time_micro();
		if (rem_t > 1000)
			usleep(1000);
		else if (rem_t > 500)
			usleep(500);
		else
			usleep(rem_t);
	}
	return (0);
}

long	get_time_passed(t_philo *philo)
{
	return (get_current_time() - philo->start_time);
}

long	last_meal_in_ms(t_philo *philo)
{
	return (current_time_micro() - philo->last_meal_time);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_error(T_ERR), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
