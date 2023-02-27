/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:33:55 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 16:00:26 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	n_time(t_rules *rules, t_philo *philo)
{
	int	n_meal;

	n_meal = 0;
	while (1)
	{
		if (philo->last_action == e_eat)
			++n_meal;
		action_philo(rules, philo);
		if (n_meal == rules->number_eat)
			sem_post(philo->meal);
	}
}

void	infini_time(t_rules *rules, t_philo *philo)
{
	while (1)
	{
		action_philo(rules, philo);
	}
}

void	action_philo(t_rules *rules, t_philo *philo)
{
	if (philo->last_action == e_eat)
	{
		ft_find_fork_eat(rules, philo);
		philo->last_action = e_sleep;
	}
	else if (philo->last_action == e_sleep)
	{
		ft_sleep(rules, philo);
		philo->last_action = e_think;
	}
	else
	{
		ft_think(rules, philo);
		philo->last_action = e_eat;
	}
}
