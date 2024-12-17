/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:19 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/17 20:03:28 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start_t;
	size_t	remaining_t;

	start_t = get_current_time();
	while ((get_current_time() - start_t) < milliseconds)
	{
		if (is_dead(philo))
			return (1);
		remaining_t = milliseconds - (get_current_time() - start_t);
		if (remaining_t > 500)
			usleep(500);
		else
			usleep(remaining_t);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_error(T_ERR), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(int argc, char **argv)
{
    t_sim   sim;

    if (argc == 5 || argc == 6)
	{
        if (initialize(argc, argv, &sim))
		{
			print_error("One of the arguments is not valid!\n");
            return (1);
		}
	}
    else
	{
        return (print_error("Usage: \n"), -1);
	}
	if (init_philo(&sim, sim.philos, argv))
		return (1);
	monitor_death(&sim);
    cleanup(&sim);
	return (0);
}
