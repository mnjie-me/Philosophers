/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:43:02 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/06/16 18:20:44 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_print(t_philo *philo, char *status, int dead)
{
	pthread_mutex_lock(philo->death);
	if (*philo->dead && !dead)
	{
		pthread_mutex_unlock(philo->death);
		return ;
	}
	if (dead)
	{
		*philo->dead = 1;
		printf("\x1B[41m\x1B[37m%llu %d died\x1B[0m\n\n\n",
			(time_now() - philo->start), philo->id + 1);
	}
	else
	{
		printf("\x1B[3m\x1B[33m%llu\x1B[0m %d %s\n",
			(time_now() - philo->start), philo->id + 1, status);
	}
	pthread_mutex_unlock(philo->death);
}

void	philo_thinks(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	if (philo->num_philo % 2 != 0)
	{
		if (philo->id % 2 != 0)
			usleep (1000);
	}
	philo_print(philo, "is thinking\n", 0);
}

void	philo_sleeps(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	philo_print(philo, "is sleeping\n", 0);
	philo_waits(philo, philo->sleep);
	if (is_dead(philo))
		return ;
}

int lock_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->left_fork < philo->right_fork)
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    else
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    pthread_mutex_lock(first_fork);
    philo_print(philo, "has taken a fork\n", 0);
    if (is_dead(philo))
    {
        pthread_mutex_unlock(first_fork);
        return 0;
    }
    pthread_mutex_lock(second_fork);
    philo_print(philo, "has taken a fork\n", 0);
    return 1;
}

void	philo_eats(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	if (!lock_forks(philo))
		return ;
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	philo_print(philo, "\x1B[43m\x1B[30m\x1B[3mis eating\x1B[0m\n", 0);
	pthread_mutex_lock(&philo->last_mutex);
	philo->last = time_now();
	pthread_mutex_unlock(&philo->last_mutex);
	philo_waits(philo, philo->eat);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);	
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	usleep (5000);
}
