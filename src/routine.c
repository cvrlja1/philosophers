/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:40:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/31 00:23:50 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	if (ft_usleep(philo->sleep_t, philo))
		return (1);
	return (0);
}

int	philo_think(t_philo *philo)
{
	long rem_t;


	pthread_mutex_lock(&philo->meal);
	rem_t = (philo->die_t - (get_current_time() - (philo->last_meal_time / 1000)));
	pthread_mutex_unlock(&philo->meal);
	if (rem_t <= philo->eat_t)
	{
		print_state(philo, "is thinking");
		return (0);
	}
	philo->think_t = rem_t - philo->eat_t;
	if (philo->think_t < 0)
		philo->think_t = 0;
	if (philo->think_t > 200)
		philo->think_t = 200;
	print_state(philo, "is thinking");
	if (ft_usleep(philo->think_t, philo))
		return (1);
	return (0);
}

int	philo_eat_odd(t_philo *philo)
{
	if (philo->odd)
		usleep(450);
	pthread_mutex_lock(&philo->left_fork);
	print_state(philo, "has taken a fork");
	if (is_dead(philo))
		return (pthread_mutex_unlock(&philo->left_fork));
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal);
	philo->last_meal_time = current_time_micro();
	pthread_mutex_unlock(&philo->meal);
	print_state(philo, "is eating");
	ft_usleep(philo->eat_t, philo);
	pthread_mutex_lock(&philo->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (1);
}

int	philo_eat_even(t_philo *philo)
{
	if (!philo->odd)
		usleep(1000);
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	if (is_dead(philo))
		return (pthread_mutex_unlock(philo->right_fork));
	pthread_mutex_lock(&philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal);
	philo->last_meal_time = current_time_micro();
	pthread_mutex_unlock(&philo->meal);
	print_state(philo, "is eating");
	ft_usleep(philo->eat_t, philo);
	pthread_mutex_lock(&philo->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	if (philo->philo_count == 1)
		return (one_philo(philo), NULL);
	while (!is_dead(philo))
	{
		if (philo->id % 2)
			philo_eat_odd(philo);
		else
			philo_eat_even(philo);
		if (philo_sleep(philo))
			break ;
		if (philo_think(philo))
			break ;
	}
	return (NULL);
}
