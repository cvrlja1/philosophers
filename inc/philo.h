/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:34 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/30 19:23:33 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ---------> Includes <----------*/

# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

/* -------> Error's <----------*/

# define M_ERR "Memory allocation failed\n"
# define T_ERR "gettimeofday() error\n"
# define MU_ERR "Failed to initialize mutex\n"
# define TH_ERR "Error creating threads\n"

/* ---------> Structures <--------*/

typedef struct s_philo
{
	int				id;
	int				meals_to_eat;
	int				meals_eaten;
	long			last_meal_time;
	long			sleep_t;
	long			eat_t;
	long			die_t;
	long			think_t;
	long			start_time;
	pthread_t		thread_id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*monitor;
	pthread_mutex_t	*start;
	pthread_mutex_t	meal;
	int				philo_count;
	int				*sim_stop;
	bool			odd;
}	t_philo;

typedef struct s_simulation
{
	int				stop;
	int				philo_count;
	pthread_mutex_t	start;
	pthread_mutex_t	monitor;
	t_philo			*philos;
}	t_sim;

int				ft_atoi(const char *nptr);
int				initialize(int ac, char **av, t_sim *sim);
long			get_current_time(void);
void			print_state(t_philo *philo, char *state);
int				init_sim(t_sim *sim);
int				init_philo(t_sim *sim, t_philo *philo, char **av);
int				init_forks(t_sim *sim, t_philo *philo);
void			*philo_routine(void *arg);
int				has_philo_died(t_philo *philo);
void			*monitor(t_sim *sim);
void			monitor_death(t_sim *sim);
void			cleanup(t_sim *sim);
void			print_error(char *msg);
int				is_dead(t_philo *philo);
int				ft_usleep(long milliseconds, t_philo *philo);
int				create_threads(t_philo *philo, t_sim *sim);
void			one_philo(t_philo *philo);
void			fork_mutex_fail(t_philo *philo, int i);
void			meal_mutex_fail(t_philo *philo, int i);
long			get_time_passed(t_philo *philo);
long			last_meal_in_ms(t_philo *philo);
unsigned long	current_time_micro(void);
#endif