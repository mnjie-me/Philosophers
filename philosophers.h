/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:38:40 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/20 14:55:30 by mnjie-me         ###   ########.fr       */
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
	int				have_eaten;
	int				need_food;
	int				*dead_alive;
	t_time			die;
	t_time			eat;
	t_time			sleep;
	t_time			start;
	t_time			last;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*death;
} t_philo;

void	philo_init(t_philo *philo, int ac, char **av);

# endif