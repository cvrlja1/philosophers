/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:34 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/18 16:45:30 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

/* ---------> Includes <----------*/

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

/* -------> Error's <----------*/

#define M_ERR "memory allocation failed\n"
#define T_ERR "gettimeofday() error\n"
#define MU_ERR "failed to initialize mutex\n"
#define TH_ERR "error creating threads\n"

/* ---------> Structures <--------*/

typedef struct s_philo
{
	int id;
	int meals_to_eat;
	int meals_eaten;
	long last_meal_time;
	long time_to_sleep;
	long time_to_eat;
	long time_to_die;
	long time_to_think;
	long start_time;
	pthread_t thread_id;
	pthread_mutex_t left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *monitor;
	pthread_mutex_t *start;
	pthread_mutex_t meal;
	pthread_mutex_t *print;
	int	philo_count;
	int *sim_stop;
} t_philo;

typedef struct s_simulation
{
	int	stop;
	int	philo_count;
	pthread_mutex_t start;
	pthread_mutex_t monitor;
	pthread_mutex_t print;
	t_philo *philos;
} t_sim;

int ft_atoi(const char *nptr);
int initialize(int ac, char **av, t_sim *sim);
size_t get_current_time(void);
void print_state(t_philo *philo, char *state);
void init_sim(t_sim *sim);
int init_philo(t_sim *sim, t_philo *philo, char **av);
void init_forks(t_sim *sim, t_philo *philo);
void *philo_routine(void *arg);
int has_philo_died(t_philo *philo);
void *monitor(t_sim *sim);
int	monitor_death(t_sim *sim);
void cleanup(t_sim *sim);
void print_error(char *msg);
int	is_dead(t_philo *philo);
int	ft_usleep(size_t milliseconds, t_philo *philo);
#endif