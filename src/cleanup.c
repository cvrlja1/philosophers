/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:40:47 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/26 20:28:44 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_state(philo, "has taken a fork");
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		return ;
	}
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->monitor);
	if (*philo->sim_stop)
		return (pthread_mutex_unlock(philo->monitor), 1);
	pthread_mutex_unlock(philo->monitor);
	return (0);
}

void	cleanup(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
		pthread_join(sim->philos[i].thread_id, NULL);
	i = -1;
	while (++i < sim->philo_count)
	{
		pthread_mutex_destroy(&sim->philos[i].left_fork);
		pthread_mutex_destroy(&sim->philos[i].meal);
	}
	pthread_mutex_destroy(&sim->monitor);
	pthread_mutex_destroy(&sim->start);
	free(sim->philos);
}

void	meal_mutex_fail(t_philo *philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&philo[i].meal);
		j++;
	}
}

void	fork_mutex_fail(t_philo *philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&philo[i].left_fork);
		j++;
	}
}
