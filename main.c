/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:38:17 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/23 19:32:27 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	final_meals(t_philo *philo, char **av)
{
	if (philo->has_eaten && philo->has_eaten == ft_atol(av[5]))
	{
		if (philo->has_eaten == 1)
			printf("\x1B[47m\x1B[31m\x1B[1m\nAll Philos ate %d \
				time\x1B[0m\n\n\n", philo->has_eaten);
		else
			printf("\x1B[47m\x1B[31m\x1B[1m\nAll Philos ate %d \
				times\x1B[0m\n\n\n", philo->has_eaten);
	}
	else
		return ;
}

void	ft_free(t_philo *philo, pthread_mutex_t *cutlery, \
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

int	wrong_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '\0')
			return (1);
		if (av[i][0] == '0' && av[i][1] == '\0')
			return (1);
		if (atol(av[1]) <= 0)
			return (1);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*cutlery;
	pthread_mutex_t	*death;

	if (wrong_args(ac, av))
	{
		write(2, "\x1B[31mError: wrong arguments\x1B[0m\n", 32);
		return (1);
	}
	if (!is_valid(av[1]) || !is_valid(av[2]) || !is_valid(av[3]))
	{
		write(2, "\x1B[31mError: wrong argument(s)\x1B[0m\n", 34);
		return (1);
	}
	philo = malloc(sizeof(t_philo) * ft_atol(av[1]));
	cutlery = malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
	death = malloc(sizeof(pthread_mutex_t));
	if (!philo || !cutlery || !death)
		return (1);
	philo_init(philo, ac, av);
	mutex_init(philo, cutlery, death);
	create_threads(philo);
	final_meals(philo, av);
	ft_free(philo, cutlery, death);
	return (0);
}
