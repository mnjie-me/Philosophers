/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:38:17 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/20 17:33:15 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    main(int ac, char **av)
{
    t_philo	*philo;
    pthread_mutex_t	*cutlery;
	pthread_mutex_t	*death;

	philo = malloc(sizeof(t_philo) * atol(av[1]));
	cutlery = malloc(sizeof(pthread_mutex_t) * atol(av[2]));
	death = malloc(sizeof(pthread_mutex_t) * atol(av[3]));

	philo_init(philo, ac, av);
	mutex_init(philo, cutlery, death);
	create_threads(philo);
	return (0);
}