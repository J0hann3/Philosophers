/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:33:55 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/13 20:23:41 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	n_time(t_mutex *philo, int nb, struct timeval *begin)
{
	int	i;

	i = 0;
	while (i < philo->number_eat)
	{
		action_philo(philo, nb, begin);
		++i;
	}
}

void	infini_time(t_mutex *philo, int nb, struct timeval *begin)
{
	while (1)
	{
		action_philo(philo, nb, begin);
	}
}
