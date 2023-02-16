/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:33:55 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 13:06:23 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	n_time(t_mutex *philo, int nb)
{
	int				i;
	struct timeval	last_meal;

	i = 0;
	last_meal = *(philo->time_begin);
	while (i < philo->number_eat)
	{
		action_philo(philo, nb, &last_meal);
		++i;
	}
	
}

void	infini_time(t_mutex *philo, int nb)
{
	struct timeval	last_meal;

	last_meal = *(philo->time_begin);
	while (1)
	{
	action_philo(philo, nb, &last_meal);
	}
}
