/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 12:59:18 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timeval	*action_philo(t_mutex *philo, int nb, struct timeval *last)
{
	int				fork[2];
	// int				chose_fork;

	(void)last;
	// Need fork to eat
	fork[0] = nb ;
	if (fork[0] >= philo->number_philo)
		fork[0] = 0;
	fork[1] = nb - 1;
	if (fork[1] < 0)
		fork[1] = philo->number_philo - 1;
	pthread_mutex_lock(&philo->mutex_fork[fork[0]]);
	pthread_mutex_lock(&philo->mutex_fork[fork[1]]);
	
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s left : %d	right : %d\n", ft_time(philo->time_begin), nb, philo->str[e_fork],
			fork[0], fork[1]);
	pthread_mutex_unlock(&philo->mutex_printf);

	// Eat
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s\n",ft_time(philo->time_begin), nb, philo->str[e_eat]);
	pthread_mutex_unlock(&philo->mutex_printf);
	gettimeofday(last, NULL);
	
	usleep(philo->time_eat * 1000);

	// Free fork
	pthread_mutex_unlock(&philo->mutex_fork[fork[0]]);
	pthread_mutex_unlock(&philo->mutex_fork[fork[1]]);
	
	// Sleep
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s\n",ft_time(philo->time_begin), nb, philo->str[e_sleep]);
	pthread_mutex_unlock(&philo->mutex_printf);
	
	usleep(philo->time_sleep * 1000);
	
	// Think
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s\n",ft_time(philo->time_begin), nb, philo->str[e_think]);
	pthread_mutex_unlock(&philo->mutex_printf);
	return (last);
}
