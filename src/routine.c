/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:40:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/10 18:26:23 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    print_state(philo, "is sleeping");
    usleep(philo->time_to_sleep * 1000);
}

void    philo_think(t_philo *philo)
{
    print_state(philo, "is thinking");
}

int    philo_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
   		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
    	pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
    	pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
    pthread_mutex_lock(philo->m_lock);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(philo->m_lock);
    print_state(philo, "is eating");
    usleep(philo->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (1);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->monitor_lock);
	if (*philo->sim_stop)
	{
		pthread_mutex_unlock(philo->monitor_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->monitor_lock);
	return (0);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!is_dead(philo))
    {
        philo_eat(philo);
        philo_think(philo);
        philo_sleep(philo);
    }
    return (NULL);
}
