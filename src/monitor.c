/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 17:07:38 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int has_philo_died(t_philo *philo)
{
    long current_time = get_current_time();
    if (current_time - philo->last_meal_time >= philo->sim->time_to_die)
    {
        print_state(philo, "died");
        return 1;
    }
    return 0;
}

void *monitor_death(void *arg)
{
    t_sim *sim = (t_sim *)arg;
    
    while (!sim->simulation_stop)
    {
        int i = 0;
        while (i < sim->number_of_philos)
        {
            if (has_philo_died(&sim->philos[i]))
            {
                sim->simulation_stop = 1;
                break;
            }
            i++;
        }
    }
    return NULL;
}


void    print_state(t_philo *philo, char *state)
{
    long    timestamp;

    timestamp = get_current_time() - philo->sim->start_time;
    pthread_mutex_lock(&philo->sim->monitor_lock);
    printf("%ld %d %s\n", timestamp, philo->id, state);
    pthread_mutex_unlock(&philo->sim->monitor_lock);
}
