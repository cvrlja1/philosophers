/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:40:12 by cvrlja            #+#    #+#             */
/*   Updated: 2025/01/07 13:39:33 by nicvrlja         ###   ########.fr       */
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
	print_state(philo, "is thinking");
	if (philo->think_t)
		if (ft_usleep(philo->think_t, philo))
			return (1);
	return (0);
}

int	philo_eat_odd(t_philo *philo)
{
	if (philo->odd)
		usleep(50);
	pthread_mutex_lock(&philo->left_fork);
	print_state(philo, "has taken a fork");
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
		usleep(750);
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
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
