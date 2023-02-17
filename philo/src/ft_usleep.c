/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:03:36 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 19:05:40 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time, t_philo *philo, t_rules *rules)
{
	long	i;

	i = 0;
	while (rules->time_die > ft_time(&philo->last_meal) && i <= time)
	{
		i = i + 1;
		usleep(1000);
	}
	// printf("philo : %d	die : %d	time : %ld	last : %ld	diff : %ld\n", philo->nb, rules->time_die,
	// 		timestamp(), last, timestamp() - last);
	pthread_mutex_lock(&rules->mutex_died);
	if (rules->time_die <= ft_time(&philo->last_meal) && rules->is_died != 1)
	{
		ft_died(rules, philo);
	}
	pthread_mutex_unlock(&rules->mutex_died);
	
}