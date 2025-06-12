/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:43:02 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/06/12 15:19:46 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_print(t_philo *philo, char *status, int dead)
{
	pthread_mutex_lock(philo->death);
	if (!*philo->dead)
	{
		printf("At \x1B[3m\x1B[33m%llu\x1B[0mms ", (time_now() - philo->start));
		printf("%d %s\n", philo->id + 1, status);
	}
	if (dead)
	{
		*philo->dead = 1;
		printf("\x1B[41m\x1B[37mAt %llums Philosopher %d died\x1B[0m\n\n\n", \
		(time_now() - philo->start), philo->id + 1);
	}
	pthread_mutex_unlock(philo->death);
	is_dead(philo);
}

void	philo_thinks(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	philo_print(philo, "is thinking\n", 0);
}

void	philo_sleeps(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	philo_print(philo, "is sleeping\n", 0);
	philo_waits(philo, philo->sleep);
}

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken left fork\n", 0);
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken right fork\n", 0);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken right fork\n", 0);
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken left fork\n", 0);
	}
}

void	philo_eats(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	lock_forks(philo);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->death);
	philo->has_eaten++;
	philo->last = time_now();
	pthread_mutex_unlock(philo->death);
	philo_print(philo, "\x1B[43m\x1B[30m\x1B[3mis eating\x1B[0m\n", 0);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo_waits(philo, philo->eat);
}
