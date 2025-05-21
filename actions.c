/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:43:02 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/20 17:54:56 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_philo *philo, char *status, int kill)
{
	pthread_mutex_lock(philo->death);
	if (!*philo->dead)
		printf("%llu, %d, %s", (ft_get_time() - philo->start), philo->id + 1, status);
	if (kill)
	{
		*philo->dead = 1;
		printf ("%llu %d died\n", (ft_get_time() - philo->start), philo->id + 1);
	}
	pthread_mutex_unlock(philo->death);
    is_dead(philo);
}