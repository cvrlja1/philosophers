/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 22:13:21 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int has_philo_died(t_philo *philo, t_sim *sim)
{
    long current_time = get_current_time();
    pthread_mutex_lock(&sim->meal_lock);
    if (current_time - philo->last_meal_time >= sim->time_to_die)
    {
        pthread_mutex_unlock(&sim->meal_lock);
        print_state(philo, "died");
        return 1;
    }
    pthread_mutex_unlock(&sim->meal_lock);
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
            pthread_mutex_lock(&sim->monitor_lock);
            if (has_philo_died(&sim->philos[i], sim))
            {
                sim->simulation_stop = 1;
                pthread_mutex_unlock(&sim->monitor_lock);
                break;
            }
            pthread_mutex_unlock(&sim->monitor_lock);
            i++;
        }
    }
    return NULL;
}


void    print_state(t_philo *philo, char *state)
{
    long    timestamp;

    pthread_mutex_lock(philo->m_print);
    timestamp = get_current_time() - philo->start_time;
    printf("%ld %d %s\n", timestamp, philo->id, state);
    pthread_mutex_unlock(philo->m_print);
}
