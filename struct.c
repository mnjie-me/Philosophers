/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:35:30 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/20 14:18:59 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_init(t_philo *philo, int ac, char **av)
{
	int	i;
	int	*dead_alive;

	i = 0;
	dead_alive =  malloc(sizeof(int))
	while (i <= atol(av[1]))
	{
		philo[i].id = i;
		philo[i].have_eaten = 0;
		philo[i].dead_alive = dead_alive;
		philo[i].die = atol(av[2]);
		philo[i].eat = atol(av[3]);
		philo[i].sleep = atol(av[4]);
		if (ac == 6)
			philo[i].need_food = atol(av[5])
		else
			philo[i].need_food = -1; // come de forma infinita
		philo[i].start = get_time();
		philo[i].last = get_time();
	}
}