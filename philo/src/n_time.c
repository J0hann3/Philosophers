/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:33:55 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 13:36:01 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	n_time(t_rules *rules, t_philo *philo)
{
	int				i;

	i = 0;
	pthread_mutex_lock(&rules->mutex_died);
	while (rules->is_died != 1 && i < rules->number_eat)
	{
		pthread_mutex_unlock(&rules->mutex_died);
		action_philo(rules, philo);
		++i;
		pthread_mutex_lock(&rules->mutex_died);
	}
	pthread_mutex_unlock(&rules->mutex_died);
}

void	infini_time(t_rules *rules, t_philo *philo)
{
	
	pthread_mutex_lock(&rules->mutex_died);
	while (rules->is_died != 1)
	{
		pthread_mutex_unlock(&rules->mutex_died);
		action_philo(rules, philo);
		pthread_mutex_lock(&rules->mutex_died);
	}
	pthread_mutex_unlock(&rules->mutex_died);
}
