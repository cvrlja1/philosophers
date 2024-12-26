/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:42:19 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/26 20:15:17 by nicvrlja         ###   ########.fr       */
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
		return (print_error("Usage: \n"), 1);
	}
	if (init_philo(&sim, sim.philos, argv))
		return (1);
	if (init_forks(&sim, sim.philos))
		return (1);
	if (create_threads(sim.philos, &sim))
		return (1);
	monitor_death(&sim);
	cleanup(&sim);
	return (0);
}
