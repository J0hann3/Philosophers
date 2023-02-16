/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:03:36 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 18:07:07 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time, long last_meal, t_mutex *philo)
{
	long	i;

	i = 0;
	// printf("die : %d	diff : %ld	time : %ld\n", philo->time_die, timestamp() - last_meal, time);

	while (philo->time_die >= timestamp() - last_meal && i < time)
	{
		i = i + 1;
		usleep(1000);
	}
	if (philo->time_die <= timestamp() - last_meal)
	{
		pthread_mutex_lock(&philo->mutex_printf);
		printf("%d                    %s\n",ft_time(philo->time_begin), philo->str[e_die]);
		pthread_mutex_unlock(&philo->mutex_printf);
	}
}