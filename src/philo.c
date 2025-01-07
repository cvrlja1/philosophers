/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:19 by cvrlja            #+#    #+#             */
/*   Updated: 2025/01/07 13:41:30 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim	sim;

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
		print_error("Usage: number_of_philosophers time_to_die time_to_eat ti"
			"me_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (init_philo(&sim, sim.philos, argv))
		return (1);
	if (init_forks(&sim, sim.philos))
		return (1);
	if (create_threads(sim.philos, &sim))
		return (1);
	cleanup(&sim);
	return (0);
}
