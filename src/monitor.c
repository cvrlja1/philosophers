/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/17 20:03:42 by nicvrlja         ###   ########.fr       */
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

int	all_philos_ate(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->philo_count)
	{
		pthread_mutex_lock(&philo[i].meal);
		if (philo[i].meals_to_eat == -1 || philo[i].meals_eaten < philo[i].meals_to_eat)
			return (pthread_mutex_unlock(&philo[i].meal), 0);
		pthread_mutex_unlock(&philo[i].meal);
	}
	return (1);
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
			if (all_philos_ate(philo))
			{
				pthread_mutex_lock(philo->monitor);
				*philo[i].sim_stop = 1;
				pthread_mutex_unlock(philo->monitor);
				return (0);
			}
       		if (philo_died(&philo[i]))
			{
				print_state(&philo[i], "died");
				pthread_mutex_lock(philo->monitor);
				*philo[i].sim_stop = 1;
				pthread_mutex_unlock(philo->monitor);
				return (1);
			}
		}
		usleep(100);
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
