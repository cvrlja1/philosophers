/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicvrlja <nicvrlja@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:34:16 by nicvrlja          #+#    #+#             */
/*   Updated: 2024/12/26 17:50:20 by nicvrlja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		write(2, &msg[i], 1);
	write(2, "\n", 1);
}
