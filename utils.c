/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnjie-me <mnjie-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:03:12 by mnjie-me          #+#    #+#             */
/*   Updated: 2025/05/21 17:38:59 by mnjie-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_time	time_now(void)
{
	struct timeval	tp;
	t_time			time;
	
	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

long	ft_atol(const char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] =='\t')
		i++;
	if ( str[i] == '-')
		return (1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}

int	is_valid(const char *av)
{
	int	i;

	i = 0;
	if (!av || av[0] == '\0')
		return (0);
	while (av[i] == ' ' || av[i] =='\t')
		i++;
	if ( av[i] == '-')
		return (0);
	if (av[i] == '+')
		i++;
	if (av[i] < '0' || av[i] > '9')
		return (0);
	while (av[i] >= '0' && av[i] <= '9')
		i++;
	if (av[i] != '\0')
		return (0);
	return (1);
}