/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 18:09:21 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action_philo(t_mutex *philo, int nb, struct timeval *last)
{
	ft_sleep(philo, nb, last);
	ft_find_fork(philo, nb, last);
	ft_think(philo, nb);
}

void	ft_eat(t_mutex *philo, int nb, struct timeval *last)
{
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s\n",ft_time(philo->time_begin), nb, philo->str[e_eat]);
	pthread_mutex_unlock(&philo->mutex_printf);
	gettimeofday(last, NULL);
	ft_usleep(philo->time_eat, time_conv(last), philo);
}

void	ft_think(t_mutex *philo, int nb)
{
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s\n",ft_time(philo->time_begin), nb, philo->str[e_think]);
	pthread_mutex_unlock(&philo->mutex_printf);
}


void	ft_sleep(t_mutex *philo, int nb, struct timeval *last)
{
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s\n",ft_time(philo->time_begin), nb, philo->str[e_sleep]);
	pthread_mutex_unlock(&philo->mutex_printf);
	ft_usleep(philo->time_sleep, time_conv(last), philo);
}

void	ft_find_fork(t_mutex *philo, int nb, struct timeval *last)
{
	int	fork[2];

	fork[0] = nb ;
	if (fork[0] >= philo->number_philo)
		fork[0] = 0;
	fork[1] = nb - 1;
	if (fork[1] < 0)
		fork[1] = philo->number_philo - 1;
	pthread_mutex_lock(&philo->mutex_fork[fork[0]]);
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %s left : %d\n", ft_time(philo->time_begin), nb, philo->str[e_fork],
			fork[0]);
	pthread_mutex_unlock(&philo->mutex_printf);
	pthread_mutex_lock(&philo->mutex_fork[fork[1]]);
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%d %d %sright : %d\n", ft_time(philo->time_begin), nb, philo->str[e_fork], fork[1]);
	pthread_mutex_unlock(&philo->mutex_printf);
	ft_eat(philo, nb, last);
	pthread_mutex_unlock(&philo->mutex_fork[fork[0]]);
	pthread_mutex_unlock(&philo->mutex_fork[fork[1]]);
}
