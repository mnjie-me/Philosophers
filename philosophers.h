/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:38:40 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/23 19:29:16 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef unsigned long long	t_time;

typedef struct s_philo
{
	int				id;
	int				num_philo;
	int				has_eaten;
	int				need_food;
	int				*dead;
	t_time			time_die;
	t_time			eat;
	t_time			sleep;
	t_time			start;
	t_time			last;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*death;
}	t_philo;

void	philo_init(t_philo *philo, int ac, char **av);
void	mutex_init(t_philo *philo, pthread_mutex_t *cutlery, \
	pthread_mutex_t *death);

void	create_threads(t_philo *philo);
void	*philo_routine(void *args);
int		is_dead(t_philo *philo);

void	philo_eats(t_philo *philo);
void	philo_sleeps(t_philo *philo);
void	philo_thinks(t_philo *philo);
void	philo_print(t_philo *philo, char *status, int dead);
int		philo_waits(t_philo *philo, t_time wait_time);

int		is_valid(const char *av);
long	ft_atol(const char *av);
t_time	time_now(void);

#endif