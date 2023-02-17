/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 13:43:22 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action_philo(t_rules *rules, t_philo *philo)
{
	if (philo->last_action == e_eat)
	{
		ft_find_fork(rules, philo);
		philo->last_action = e_sleep;
	}
	else
	{
		ft_sleep(rules, philo);
		philo->last_action = e_eat;
	}
}

void	ft_died(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_die);
}

void	ft_sleep(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_sleep);
	ft_usleep(rules->time_sleep, philo, rules);
}

void	ft_find_fork(t_rules *rules, t_philo *philo)
{
	ft_think(rules, philo);
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	ft_printf(rules, philo, e_fork);
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_2]);
	ft_printf(rules, philo, e_fork);
	ft_eat(rules, philo);
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_2]);
}

void	ft_think(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_think);
}

void	ft_eat(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_eat);
	gettimeofday(&philo->last_meal, NULL);
	ft_usleep(rules->time_eat, philo, rules);
}
