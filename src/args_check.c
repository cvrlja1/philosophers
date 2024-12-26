/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:29:15 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/26 19:40:29 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		if (i == 1 && ft_atoi(av[i]) > 200)
			return (1);
		if (ft_atoi(av[i]) <= 0)
			return (1);
	}
	return (0);
}

int	initialize(int ac, char **av, t_sim *sim)
{
	int	i;

	if (init_sim(sim))
		return (1);
	if (check_args(ac, av))
		return (1);
	sim->philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!sim->philos)
	{
		print_error(M_ERR);
		exit(1);
	}
	sim->philo_count = ft_atoi(av[1]);
	i = -1;
	while (++i < sim->philo_count)
		memset(&sim->philos[i], 0, sizeof(t_philo));
	return (0);
}
