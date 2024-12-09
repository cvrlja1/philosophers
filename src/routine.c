/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:40:12 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 22:13:44 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int sim_stop(t_philo *philo)
{
    pthread_mutex_lock(philo->m_lock);
    if (*philo->sim_stop)
    {
        pthread_mutex_unlock(philo->m_lock);
        return (1);
    }
    pthread_mutex_unlock(philo->m_lock);
    return (0);
}

void    philo_sleep(t_philo *philo)
{
    print_state(philo, "is sleeping");
    usleep(philo->time_to_sleep * 1000);
}

void    philo_think(t_philo *philo)
{
    print_state(philo, "is thinking");
}

int    philo_eat_even(t_philo *philo)
{
    if (sim_stop(philo))
        return (0);
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->left_fork));
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(philo->meal_lock);
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    print_state(philo, "is eating");
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    usleep(philo->time_to_eat * 1000);
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (1);
}

int    philo_eat_odd(t_philo *philo)
{
    if (sim_stop(philo))
        return (0);
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork));
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(philo->meal_lock);
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    print_state(philo, "is eating");
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    usleep(philo->time_to_eat * 1000);
    if (sim_stop(philo))
        return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork));
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    return (1);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
         if (philo->id % 2)
        {
            ft_usleep(1);
            if (sim_stop(philo))
                break ;
            philo_eat_odd(philo);
            if (sim_stop(philo))
                break ;
            philo_sleep(philo);
            if (sim_stop(philo))
                break ;
            philo_think(philo);
        }
        else
        {
            if (sim_stop(philo))
                break ;
            philo_eat_even(philo);
            if (sim_stop(philo))
                break ;
            philo_think(philo);
            if (sim_stop(philo))
                break ;
            philo_sleep(philo);
        }
    }
    return (NULL);
}
