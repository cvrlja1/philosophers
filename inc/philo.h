/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:34 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 17:06:01 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

/* ---------> Includes <----------*/

# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/* ---------> Structures <--------*/

typedef struct s_philo
{
    int id;
    int meals;
    long    last_meal_time;
    pthread_t   thread_id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_simulation *sim;
}   t_philo;

typedef struct s_simulation
{
    int number_of_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long start_time;
    int meals_required;
    int simulation_stop;
    pthread_mutex_t monitor_lock;
    pthread_t   monitor;
    t_philo *philos;
    pthread_mutex_t *forks;
} t_sim;

int	ft_atoi(const char *nptr);
int args_check(int ac, char **av, t_sim *sim);
size_t	get_current_time(void);
void    print_state(t_philo *philo, char *state);
void    init_sim(t_sim *sim);
void    init_philo(t_sim *sim, t_philo *philo);
void    init_forks(t_sim *sim);
void    *philo_routine(void *arg);
int has_philo_died(t_philo *philo);
void *monitor_death(void *arg);
void    cleanup(t_sim *sim);
#endif