/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:08:37 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 21:39:24 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_sim(t_sim *sim)
{
    memset((void *)sim, 0, sizeof(t_sim));
    pthread_mutex_init(&sim->monitor_lock, NULL);
    pthread_mutex_init(&sim->monitor_print, NULL);
    pthread_mutex_init(&sim->meal_lock, NULL);
}

void create_threads(t_philo *philo, t_sim *sim)
{
    int i;

    i = -1;
    while (++i < sim->number_of_philos)
    {
     if (pthread_create(&philo[i].thread_id, NULL, philo_routine, (void *)&philo[i]))
        {
            printf("Error creating philo thread %d\n", i + 1);
            exit(1);
        }
    }
}

void    init_philo(t_sim *sim, t_philo *philo)
{
    int i;

    i = -1;
    while (++i < sim->number_of_philos)
    {
        philo[i].id = i + 1;
        philo[i].sim_stop = &sim->simulation_stop;
        philo[i].meal_lock = &sim->meal_lock;
        philo[i].meals = 0;
        philo[i].last_meal_time = get_current_time();
        philo[i].start_time = get_current_time();
        philo[i].time_to_eat = sim->time_to_eat;
        philo[i].time_to_sleep = sim->time_to_sleep;
        philo[i].m_lock = &sim->monitor_lock;
        philo[i].m_print = &sim->monitor_print;
        philo[i].left_fork = &sim->forks[i];
        philo[i].right_fork = &sim->forks[(i + 1) % sim->number_of_philos];
    }
    create_threads(philo, sim);
}

void    init_forks(t_sim *sim)
{
    int i;

    i = -1;
    while (++i < sim->number_of_philos)
        pthread_mutex_init(&sim->forks[i], NULL);
}
