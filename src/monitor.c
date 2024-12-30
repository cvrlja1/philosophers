/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/30 14:01:43 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	if (last_meal_in_ms(philo) >= philo->die_t)
		return (pthread_mutex_unlock(&philo->meal), 1);
	pthread_mutex_unlock(&philo->meal);
	return (0);
}

int	philo_died(t_philo *philo, t_sim *sim)
{
	int		i;

	i = -1;
	while (++i < philo->philo_count)
	{
		if (check_dead(&philo[i]))
		{
			pthread_mutex_lock(&sim->monitor);
			*philo[i].sim_stop = 1;
			printf("%ld %d %s\n", get_current_time() - philo[i].start_time,
				philo[i].id, "died");
			pthread_mutex_unlock(&sim->monitor);
			return (1);
		}
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

void	monitor_death(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
		sim->philos[i].last_meal_time = get_current_time();
	pthread_mutex_unlock(&sim->start);
	while (1)
	{
		if (all_philos_ate(sim->philos) || philo_died(sim->philos, sim))
			break ;
		usleep(100);
	}
}

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(philo->monitor);
	if (!*philo->sim_stop)
	{
		printf("%ld %d %s\n", get_time_passed(philo), philo->id, state);
		pthread_mutex_unlock(philo->monitor);
		return ;
	}
	pthread_mutex_unlock(philo->monitor);
}
