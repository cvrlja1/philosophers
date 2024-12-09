/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:19 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 18:18:31 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(int argc, char **argv)
{
    t_sim   sim;

    init_sim(&sim);
    if (argc == 5 || argc == 6)
    {
        if (!args_check(argc, argv, &sim))
            return (-1);
    }
    else
        return(printf("Error\n"), -1);
    sim.philos = malloc(sizeof(t_philo) * sim.number_of_philos);
    if (!sim.philos)
        return (perror("malloc fail"), -1);
    sim.forks = malloc(sizeof(pthread_mutex_t) * sim.number_of_philos);
    if (!sim.forks)
        return (perror("malloc fail"), -1);
    init_forks(&sim);
    init_philo(&sim, sim.philos);
    pthread_create(&sim.monitor, NULL, monitor_death, (void *)&sim);
    pthread_join(sim.monitor, NULL);
    cleanup(&sim);
}
