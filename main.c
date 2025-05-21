/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:38:17 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/21 17:56:23 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_free(t_philo *philo, pthread_mutex_t *cutlery, \
	pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(cutlery);
	pthread_mutex_destroy(philo->death);
	free(philo->dead);
	free(philo);
	free(cutlery);
	free(death);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		while (av[i])
		{
			j = 0;
			while (av[i][j])
			{
				if (av[i][j] < 48 && av[i][j] > 56)
					return (1);
				if (av[i][0] == 48)
					return (1);
				j++;
			}
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int    main(int ac, char **av)
{
    t_philo	*philo;
    pthread_mutex_t	*cutlery;
	pthread_mutex_t	*death;

	if (!check_args(ac, av))
		return (1);
	if (!is_valid(av[1]) || !is_valid(av[2]) || !is_valid(av[3]))
	{
		write(2, "Error: wrong arguments\n", 23);
		return (1);
	}
	philo = malloc(sizeof(t_philo) * ft_atol(av[1]));
	cutlery = malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
	death = malloc(sizeof(pthread_mutex_t));
	if (!philo || !cutlery || !death)
	{
		write(2, "malloc failed\n", 14);
		return (1);
	}
	philo_init(philo, ac, av);
	mutex_init(philo, cutlery, death);
	create_threads(philo);
	printf("\nestoy aquí\n");
	printf("\x1B[47m\x1B[31m\n%d philosophers have eaten\x1B[0m\n", philo->has_eaten);
	ft_free(philo, cutlery, death);
	return (0);
}