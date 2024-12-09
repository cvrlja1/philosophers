/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:40:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 17:10:41 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    print_state(philo, "is sleeping");
    usleep(philo->sim->time_to_sleep * 1000);
}

void    philo_think(t_philo *philo)
{
    print_state(philo, "is thinking");
    usleep(1000);
}

void    philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    philo->last_meal_time = get_current_time();
    print_state(philo, "is eating");
    usleep(philo->sim->time_to_eat * 1000);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    *philo_routine(void *arg)
{
    t_sim   *sim;
    t_philo *philo;

    philo = (t_philo *)arg;
    sim = philo->sim;
    while (!sim->simulation_stop)
    {
        philo_think(philo);
        philo_eat(philo);
        philo_sleep(philo);
    }
    return (NULL);
}
