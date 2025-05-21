/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:43:02 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/21 16:29:04 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_waits(t_philo *philo, t_time wait_time)
{
	t_time	time;
	
	time = time_now(); // hacer esta función
	while (time_now() - time < wait_time)
	{
		if (is_dead(philo))
			return (1);
		usleep(10);
	}
	return (0);
}

void	philo_print(t_philo *philo, char *status, int dead)
{
	pthread_mutex_lock(philo->death);
	if (!*philo->dead)
		printf("At %llums philo %d %s", (time_now() - philo->start), philo->id + 1, status);
	if (dead)
	{
		*philo->dead = 1;
		printf ("At %llums philo %d died\n", (time_now() - philo->start), philo->id + 1);
	}
	pthread_mutex_unlock(philo->death);
    is_dead(philo);
}

void philo_thinks(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	philo_print(philo, "is thinking", 0);
}

void philo_sleeps(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (is_dead(philo))
		return ;
	philo_print(philo, "is sleeping", 0);
	philo_waits(philo, philo->sleep);
}

void	philo_eats(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(philo->left_fork);
	philo_print(philo, "takes left fork", 0);
	pthread_mutex_lock(philo->right_fork);
	philo_print(philo, "takes right fork", 0);
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(philo->death);
	philo->has_eaten++;
	pthread_mutex_unlock(philo->death);
	philo_print(philo, "is eaten", 0);
	philo_waits(philo, philo->eat); // hacer esta funcion que permite que se ejecuten otros hilos para mejor rendimiento y sincronización
	pthread_mutex_lock(philo->death);
	philo->last = time_now();
	pthread_mutex_unlock(philo->death);
	if (is_dead(philo))
		return ;
}