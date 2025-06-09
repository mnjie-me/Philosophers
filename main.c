/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:38:17 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/06/09 16:17:51 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	final_meals(t_philo *philo, char **av, int ac)
{
	int	i;
	int	total;
	int	need_food;

	if (ac < 6)
		return ;
	need_food = ft_atol(av[5]);
	total = philo->num_philo;
	i = 0;
	while (i < total)
	{
		if (philo[i].has_eaten < need_food)
			return ;
		i++;
	}
	if (need_food == 1)
		printf("\x1B[47m\x1B[31m\x1B[1m\nAll Philos ate %d \
			time\x1B[0m\n\n\n", need_food);
	else
		printf("\x1B[47m\x1B[31m\x1B[1m\nAll Philos ate %d \
			times\x1B[0m\n\n\n", need_food);
}

void	ft_free(t_philo *philo, pthread_mutex_t *cutlery, \
		pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_destroy(&cutlery[i]);
		i++;
	}
	pthread_mutex_destroy(death);
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
		if (av[i][0] == '0' && av[i][1] != '\0')
			return (1);
		if (ft_atol(av[1]) <= 0 || ft_atol(av[2]) <= 0 || ft_atol(av[3]) <= 0
			|| ft_atol(av[4]) <= 0)
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
	t_print			print;
	pthread_mutex_t	*cutlery;
	pthread_mutex_t	*death;

	if (wrong_args(ac, av))
	{
		write(2, "\x1B[31mError: wrong arguments\x1B[0m\n", 32);
		return (1);
	}
	philo = malloc(sizeof(t_philo) * ft_atol(av[1]));
	cutlery = malloc(sizeof(pthread_mutex_t) * ft_atol(av[1]));
	death = malloc(sizeof(pthread_mutex_t));
	if (!philo || !cutlery || !death)
		return (1);
	philo_init(philo, ac, av);
	mutex_init(philo, cutlery, death);
	pthread_mutex_init(&print.print_mutex, NULL);
	create_threads(philo);
	final_meals(philo, av, ac);
	ft_free(philo, cutlery, death);
	return (0);
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