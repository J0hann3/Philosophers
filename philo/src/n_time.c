/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:33:55 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 12:08:25 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	n_time(t_rules *rules, t_philo *philo)
{
	int	n_meal;

	n_meal = 0;
	pthread_mutex_lock(&rules->mutex_died);
	while (rules->is_died != 1 && rules->n_meal < (rules->number_philo))
	{
		if (philo->last_action == e_eat)
			++n_meal;
		pthread_mutex_unlock(&rules->mutex_died);
		action_philo(rules, philo);
		pthread_mutex_lock(&rules->mutex_died);
		if (n_meal == rules->number_eat)
			rules->n_meal = rules->n_meal + 1;
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
