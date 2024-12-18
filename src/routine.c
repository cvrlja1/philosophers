/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:40:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/18 17:03:09 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    print_state(philo, "is sleeping");
    ft_usleep(philo->time_to_sleep, philo);
}

void    philo_think(t_philo *philo)
{
    print_state(philo, "is thinking");
	if (philo->time_to_think)
		ft_usleep(philo->time_to_think, philo);
}

int    philo_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal);
 	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal);
	print_state(philo, "is eating");
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
    return (1);
}

int    philo_eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal);
 	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal);
	print_state(philo, "is eating");
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
    return (1);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->monitor);
	if (*philo->sim_stop)
		return (pthread_mutex_unlock(philo->monitor), 1);
	pthread_mutex_unlock(philo->monitor);
	return (0);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
    while (!is_dead(philo))
    {
		if (philo->id % 2)
		{
			usleep(100);
			philo_eat_odd(philo);
		}
		else
		{
			philo_eat_even(philo);
		}
		philo_sleep(philo);
		philo_think(philo);
	}
    return (NULL);
}
