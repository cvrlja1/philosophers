/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:19 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/16 16:49:09 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
        return (printf("Error\n"), -1);
	}
	init_forks(&sim, sim.philos);
    init_philo(&sim, sim.philos, argv);
	monitor_death(&sim);
    cleanup(&sim);
}
