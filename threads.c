/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:21:31 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/20 17:33:51 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]);
		i++;
		usleep(30); // aquí pueden ser perfectamente 100 (0.1 ms), esto deja tiempo entre cada creacion de hilos para no sobrecargar el sistema
	}
	if (is_dead(philo))
		return ;
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
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
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}		
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	if (philo->have_eaten == philo->need_food)
		return (1);
	pthread_mutex_lock(philo->death);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	if (philo->last - philo->start > philo->die)
	{
		*(philo->dead) = 1;
		philo_print(philo, "philo died", 1);
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	return (0);
}