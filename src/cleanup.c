/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:40:47 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 18:56:01 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    cleanup(t_sim *sim)
{
    int i;

    i = -1;
    while (++i < sim->number_of_philos)
        pthread_join(sim->philos[i].thread_id, NULL);
    i = -1;
    while (++i < sim->number_of_philos)
        pthread_mutex_destroy(&sim->forks[i]);
    pthread_mutex_destroy(&sim->monitor_lock);
    free(sim->philos);
    free(sim->forks);
}