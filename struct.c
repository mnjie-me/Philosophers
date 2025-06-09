/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:35:30 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/06/09 16:13:47 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_init(t_philo *philo, pthread_mutex_t *cutlery, \
		pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		philo[i].left_fork = &cutlery[i];
		philo[i].right_fork = &cutlery[(i + 1) % philo->num_philo];
		i++;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].right_fork, NULL);
		philo[i].death = death;
		i++;
	}
	pthread_mutex_init(death, NULL);
}

void	philo_init(t_philo *philo, int ac, char **av)
{
	int	i;
	int	*dead;

	i = 0;
	dead = malloc(sizeof(int));
	*dead = 0;
	while (i < atol(av[1]))
	{
		philo[i].id = i;
		philo[i].has_eaten = 0;
		philo[i].dead = dead;
		philo[i].num_philo = atol(av[1]);
		philo[i].time_die = atol(av[2]);
		philo[i].eat = atol(av[3]);
		philo[i].sleep = atol(av[4]);
		if (ac == 6)
			philo[i].need_food = atol(av[5]);
		else
			philo[i].need_food = -1;
		philo[i].start = time_now();
		philo[i].last = time_now();
		i++;
	}
}
