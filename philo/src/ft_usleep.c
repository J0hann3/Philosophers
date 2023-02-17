/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:03:36 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 13:07:09 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time, t_philo *philo, t_rules *rules)
{
	long	i;
	long	last;

	i = 0;
	last = time_conv(&philo->last_meal);
	while (rules->time_die > timestamp() - last && i <= time)
	{
		i = i + 1;
		usleep(1000);
	}
	// printf("philo : %d	die : %d	time : %ld	last : %ld	diff : %ld\n", philo->nb, rules->time_die,
	// 		timestamp(), last, timestamp() - last);
	if (rules->time_die <= timestamp() - last)
	{
		ft_died(rules, philo);
	}
}