/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:21:31 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/06/09 16:41:26 by mnjie-me         ###   ########.fr       */
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
	if (time_now() - philo->last > philo->time_die)
	{
		*(philo->dead) = 1;
		pthread_mutex_unlock(philo->death);
		philo_print(philo, "Philo died\n", 1);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
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
	i = 0;
	while (i < philo->num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

/*   No pruebes con más de 200 filósofos.
    No pruebes con menos de 60 ms para time_to_die, time_to_eat o time_to_sleep.
    Prueba con 5 800 200 200. Nadie debería morir.
    Prueba con 5 800 200 200 7. Nadie debería morir y la simulación debería parar cuando todos los filósofos hayan comido como mínimo 7 veces cada uno.
    Prueba con 4 410 200 200. Nadie debería morir.
    Prueba con 4 310 200 100. Un filósofo debería morir.
    Prueba con 2 filósofos y verifica los distintos tiempos (un retraso en la muerte de más de 10 ms es inaceptable).
    Prueba con tus valores para verificar todas los requisitos. Comprueba que los filósofos mueren cuando toca, que no roban tenedores, etc.
 */