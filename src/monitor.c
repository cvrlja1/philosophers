/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/10 18:23:28 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int has_philo_died(t_philo *philo)
{
    long current_time = get_current_time();

	pthread_mutex_lock(philo->m_lock);
    if (current_time - philo->last_meal_time >= philo->time_to_die)
    {
        print_state(philo, "died");
		pthread_mutex_unlock(philo->m_lock);
        return (1);
    }
	pthread_mutex_unlock(philo->m_lock);
    return (0);
}

int	monitor_death(t_philo *philo)
{    
    int	i;

	i = -1;
    while (++i < philo->philo_count)
	{
        if (has_philo_died(&philo[i]))
		{
			pthread_mutex_lock(philo->monitor_lock);
			*philo->sim_stop = 1;
			pthread_mutex_unlock(philo->monitor_lock);
			return (1);
		}
	}
    return (0);
}

void	*monitor(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!monitor_death(philo))
			break ;
	}
	return (NULL);
}

void    print_state(t_philo *philo, char *state)
{
    long    timestamp;

	pthread_mutex_lock(philo->print_lock);
    timestamp = get_current_time() - philo->start_time;
    printf("%ld %d %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(philo->print_lock);
}
