/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvrlja <cvrlja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:29:15 by cvrlja            #+#    #+#             */
/*   Updated: 2024/12/09 16:09:03 by cvrlja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int args_check(int ac, char **av, t_sim *sim)
{
    sim->number_of_philos = ft_atoi(av[1]);
    sim->time_to_die = ft_atoi(av[2]);
    sim->time_to_eat = ft_atoi(av[3]);
    sim->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        sim->meals_required = ft_atoi(av[5]);
    else
        sim->meals_required = -1;
    return (1);
}