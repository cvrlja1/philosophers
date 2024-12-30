/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/30 18:51:33 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	if (last_meal_in_ms(philo) >= (philo->die_t * 1000))
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
			printf("%ld %d %s\n", get_time_passed(philo),
				philo[i].id, "died");
			pthread_mutex_unlock(&sim->monitor);
			return (1);
		}
	}
	return (0);
}

int	all_philos_ate(t_philo *philo, t_sim *sim)
{
	int	i;
	int	all_ate;

	i = -1;
	if (philo->meals_to_eat == -1)
		return (0);
	all_ate = 0;
	while (++i < sim->philo_count)
	{
		pthread_mutex_lock(&philo[i].meal);
		if (philo[i].meals_eaten >= philo[i].meals_to_eat)
			all_ate++;
		pthread_mutex_unlock(&philo[i].meal);
	}
	if (all_ate == sim->philo_count)
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
	int		i;
	bool	odd;

	i = -1;
	if (sim->philo_count % 2)
		odd = true;
	else
		odd = false;
	while (++i < sim->philo_count)
	{
		sim->philos[i].start_time = get_current_time();
		sim->philos[i].last_meal_time = current_time_micro();
		sim->philos[i].odd = odd;
	}
	usleep(200);
	pthread_mutex_unlock(&sim->start);
	while (1)
	{
		if (all_philos_ate(sim->philos, sim) || philo_died(sim->philos, sim))
			break ;
		usleep(200);
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
