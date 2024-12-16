/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/16 17:19:39 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	long	c_time;

	c_time = get_current_time();
	pthread_mutex_lock(&philo->meal);
	if (c_time - philo->last_meal_time >= philo->time_to_die)
		return (pthread_mutex_unlock(&philo->meal), 1);
	return (pthread_mutex_unlock(&philo->meal), 0);
}

int	monitor_death(t_sim *sim)
{    
    int	i;
	t_philo *philo;

	philo = sim->philos;
	while (1)
	{
		i = -1;
    	while (++i < philo->philo_count)
		{
       		if (philo_died(&philo[i]))
			{
				print_state(&philo[i], "died");
				pthread_mutex_lock(philo->monitor);
				*philo[i].sim_stop = 1;
				pthread_mutex_unlock(philo->monitor);
				return (1);
			}
		}
		if (sim->stop)
			break ;
	}
    return (0);
}

void    print_state(t_philo *philo, char *state)
{
    long    timestamp;

	if (!is_dead(philo))
	{
		pthread_mutex_lock(philo->print);
    	timestamp = get_current_time() - philo->start_time;
    	printf("%ld %d %s\n", timestamp, philo->id, state);
		pthread_mutex_unlock(philo->print);
	}
}
