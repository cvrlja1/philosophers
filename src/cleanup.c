/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:40:47 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/23 19:12:29 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    cleanup(t_sim *sim)
{
    int i;

    i = -1;
    while (++i < sim->philo_count)
        pthread_join(sim->philos[i].thread_id, NULL);
    i = -1;
    while (++i < sim->philo_count)
	{
        pthread_mutex_destroy(&sim->philos[i].left_fork);
		pthread_mutex_destroy(&sim->philos[i].meal);
	}
	//pthread_mutex_destroy(&sim->print);
    pthread_mutex_destroy(&sim->monitor);
	pthread_mutex_destroy(&sim->start);
    free(sim->philos);
}