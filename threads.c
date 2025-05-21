/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:21:31 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/21 18:01:33 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	if (philo->has_eaten == philo->need_food)
		return (1);
	pthread_mutex_lock(philo->death);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	if (philo->last - philo->start > philo->time_die)
	{
		*(philo->dead) = 1;
		philo_print(philo, "philo died", 1);
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	printf("\nestoy aquí 2\n");
	return (0);
}

void *philo_routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (philo->num_philo == 1 && !is_dead(philo))
	{
		pthread_mutex_lock(philo->left_fork);
			return (NULL);
		while (!is_dead(philo))
			usleep(100);
		philo_print(philo, "using left fork", 0);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		while (1)
		{
			if(is_dead(philo))
				break;
			philo_eats(philo);
			philo_sleeps(philo);
			philo_thinks(philo);
		}		
	}
	return (NULL);
}

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]);
		i++;
		usleep(100); // aquí pueden ser perfectamente 100 (0.1 ms), esto deja tiempo entre cada creacion de hilos para no sobrecargar el sistema
	}
	printf("\nestoy aquí\n");
	if (is_dead(philo))
		return ;
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}