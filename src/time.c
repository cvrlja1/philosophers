/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:14:48 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/12/30 13:59:59 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long milliseconds, t_philo *philo)
{
	long	end_t;

	end_t = get_current_time() + milliseconds;
	while (get_current_time() < end_t)
	{
		if (is_dead(philo))
			return (1);
		usleep(200);
	}
	return (0);
}

long	get_time_passed(t_philo *philo)
{
	return (get_current_time() - philo->start_time);
}

long	last_meal_in_ms(t_philo *philo)
{
	return (get_current_time() - philo->last_meal_time);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_error(T_ERR), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
