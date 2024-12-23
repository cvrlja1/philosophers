/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/23 21:17:10 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo, t_sim *sim)
{
	int		i;

	i = -1;
	while (++i < philo->philo_count)
	{
		pthread_mutex_lock(&philo[i].meal);
		if (get_current_time() - philo[i].last_meal_time >= philo[i].time_to_die)
		{
			pthread_mutex_unlock(&philo[i].meal);
			pthread_mutex_lock(&sim->monitor);
			*philo[i].sim_stop = 1;
			//pthread_mutex_lock(philo[i].print);
    		printf("%ld %d %s\n", get_current_time() - philo[i].start_time, philo[i].id, "died");
			//pthread_mutex_unlock(philo[i].print);
			pthread_mutex_unlock(&sim->monitor);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].meal);
	}
	return (0);
}

int	all_philos_ate(t_philo *philo)
{
	int	i;
	int	all_ate;

	i = -1;
	if (philo->meals_to_eat == -1)
		return (0);
	all_ate = 0;
	while (++i < philo->philo_count)
	{		
		pthread_mutex_lock(&philo[i].meal);
		if (philo[i].meals_eaten >= philo[i].meals_to_eat)
			all_ate++;
		pthread_mutex_unlock(&philo[i].meal);
	}
	if (all_ate == philo->philo_count)
	{
		pthread_mutex_lock(philo->monitor);
		*philo->sim_stop = 1;
		pthread_mutex_unlock(philo->monitor);
		return (1);
	}
	return (0);
}

int	monitor_death(t_sim *sim)
{    
	t_philo *philo;

	philo = sim->philos;
	while (1)
	{
		if (all_philos_ate(philo) || philo_died(philo, sim))
			break ;
		usleep(100);
	}
    return (0);
}

void    print_state(t_philo *philo, char *state)
{
    long    timestamp;

	pthread_mutex_lock(philo->monitor);
	if (!*philo->sim_stop)
	{
    	timestamp = get_current_time() - philo->start_time;
    	printf("%ld %d %s\n", timestamp, philo->id, state);
		pthread_mutex_unlock(philo->monitor);
		return ;
	}
	pthread_mutex_unlock(philo->monitor);
}
