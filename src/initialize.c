/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:08:37 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/30 17:41:20 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_philo *philo, int i)
{
	int	j;

	j = -1;
	pthread_mutex_lock(philo->monitor);
	*philo->sim_stop = 1;
	pthread_mutex_unlock(philo->monitor);
	while (++j < i)
		pthread_join(philo[j].thread_id, NULL);
	return (0);
}

int	init_sim(t_sim *sim)
{
	memset((void *)sim, 0, sizeof(t_sim));
	if (pthread_mutex_init(&sim->monitor, NULL))
		return (1);
	if (pthread_mutex_init(&sim->start, NULL))
		return (pthread_mutex_destroy(&sim->monitor), 1);
	return (0);
}

int	create_threads(t_philo *philo, t_sim *sim)
{
	int	i;	

	pthread_mutex_lock(&sim->start);
	i = -1;
	while (++i < sim->philo_count)
	{
		if (pthread_create(&philo[i].thread_id, NULL,
				philo_routine, (void *)&philo[i]))
		{
			pthread_mutex_unlock(&sim->start);
			join_threads(sim->philos, i);
			print_error(TH_ERR);
			free(sim->philos);
			return (1);
		}
	}
	return (0);
}

int	init_philo(t_sim *sim, t_philo *philo, char **av)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
	{
		if (av[5])
			philo[i].meals_to_eat = ft_atoi(av[5]);
		else
			philo[i].meals_to_eat = -1;
		philo[i].id = i + 1;
		philo[i].sim_stop = &sim->stop;
		philo[i].eat_t = ft_atoi(av[3]);
		philo[i].sleep_t = ft_atoi(av[4]);
		philo[i].die_t = ft_atoi(av[2]);
		philo[i].philo_count = ft_atoi(av[1]);
		if (sim->philo_count % 2 && philo[i].sleep_t < philo[i].eat_t)
			philo[i].think_t = philo[i].eat_t - philo[i].sleep_t;
		else
			philo[i].think_t = 0;
		philo[i].monitor = &sim->monitor;
		philo[i].start = &sim->start;
		philo[i].right_fork = &philo[(i + 1) % sim->philo_count].left_fork;
	}
	return (0);
}

int	init_forks(t_sim *sim, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
	{
		if (pthread_mutex_init(&philo[i].meal, NULL))
			return (meal_mutex_fail(sim->philos, i),
				print_error(MU_ERR), 1);
	}
	i = -1;
	while (++i < sim->philo_count)
	{
		if (pthread_mutex_init(&philo[i].left_fork, NULL))
			return (fork_mutex_fail(sim->philos, i),
				print_error(MU_ERR), 1);
	}
	return (0);
}
