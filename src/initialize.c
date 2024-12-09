/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:08:37 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 17:06:47 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_sim(t_sim *sim)
{
    memset((void *)sim, 0, sizeof(t_sim));
    pthread_mutex_init(&sim->monitor_lock, NULL);
    sim->start_time = get_current_time();
}

void    init_philo(t_sim *sim, t_philo *philo)
{
    int i;

    i = -1;
    while (++i < sim->number_of_philos)
    {
        philo[i].id = i + 1;
        philo[i].sim = sim;
        philo[i].meals = 0;
        philo[i].last_meal_time = get_current_time();
        philo[i].left_fork = &sim->forks[i];
        philo[i].right_fork = &sim->forks[(i + 1) % sim->number_of_philos];
        if (pthread_create(&philo[i].thread_id, NULL, philo_routine, (void *)&philo[i]))
        {
            printf("Error creating philo thread %d\n", i + 1);
            exit(1);
        }
    }
}

void    init_forks(t_sim *sim)
{
    int i;

    i = -1;
    while (++i < sim->number_of_philos)
        pthread_mutex_init(&sim->forks[i], NULL);
}
