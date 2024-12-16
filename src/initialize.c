/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:08:37 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/16 18:01:51 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_sim(t_sim *sim)
{
    memset((void *)sim, 0, sizeof(t_sim));
	pthread_mutex_init(&sim->print, NULL);
	pthread_mutex_init(&sim->monitor, NULL);
}

void create_threads(t_philo *philo)
{
    int i;

    i = -1;
    while (++i < philo->philo_count)
    {
     if (pthread_create(&philo[i].thread_id, NULL, philo_routine, (void *)&philo[i]))
        {
            print_error(TH_ERR);
            exit(1);
        }
    }
}

void    init_philo(t_sim *sim, t_philo *philo, char **av)
{
    int i;

    i = -1;
    while (++i < sim->philo_count)
    {
		if (av[5])
			philo[i].meals_to_eat = ft_atoi(av[5]);
		else
			philo[i].meals_to_eat = -1;
        philo[i].id = i + 1;
        philo[i].sim_stop = &sim->stop;
		philo[i].meals_eaten = 0;
        philo[i].last_meal_time = get_current_time();
        philo[i].start_time = get_current_time();
        philo[i].time_to_eat = ft_atoi(av[3]);
        philo[i].time_to_sleep = ft_atoi(av[4]);
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].philo_count = ft_atoi(av[1]);
		philo[i].print = &sim->print;
		philo[i].monitor = &sim->monitor;
        philo[i].right_fork = &philo[(i + 1) % philo->philo_count].left_fork;
		pthread_mutex_init(&philo[i].meal, NULL);
    }
    create_threads(philo);
}

void	init_forks(t_sim *sim, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
	{
		if(pthread_mutex_init(&philo[i].left_fork, NULL))
        {
            print_error(MU_ERR);
            exit(1);
        }
	}
}
