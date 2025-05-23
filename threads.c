/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:21:31 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/23 19:26:46 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	if (philo->need_food != -1 && philo->has_eaten == philo->need_food)
		return (1);
	pthread_mutex_lock(philo->death);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	if (time_now() - philo->last > philo->time_die)
	{
		*(philo->dead) = 1;
		philo_print(philo, "Philo died\n", 1);
		return (1);
	}
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->num_philo == 1 && !is_dead(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		philo_print (philo, "\x1B[43m\x1B[30m\x1B[3mtakes fork\x1B[0m\n", \
			0);
		while (!is_dead(philo))
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		while (1)
		{
			if (is_dead(philo))
				break ;
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
		usleep(100);
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
