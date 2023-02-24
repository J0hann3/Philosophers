/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:03:36 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 16:22:18 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(struct timeval now, long time, t_philo *philo, t_rules *rules)
{
	while ((ft_time(NULL, timestamp()) < time_conv(&now) + time)
		&& (rules->time_die > ft_time(&philo->last_meal, timestamp())))
	{
		usleep(50);
	}
	if (rules->is_died != 1 && rules->time_die <= ft_time(&philo->last_meal,
			timestamp()))
	{
		ft_died(rules, philo);
	}
}
