/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:33:55 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 19:48:31 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	n_time(t_rules *rules, t_philo *philo)
{
	int				i;

	i = 0;
	while (i < rules->number_eat)
	{
		action_philo(rules, philo);
		++i;
	}
	
}

void	infini_time(t_rules *rules, t_philo *philo)
{
	while (philo->is_died != 1)
	{
		action_philo(rules, philo);
	}
}
