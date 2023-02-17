/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 19:09:32 by jvigny           ###   ########.fr       */
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
	rules->is_died = 1;

	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s\n",ft_time(&rules->time_begin), philo->nb, rules->str[e_die]);
	pthread_mutex_unlock(&rules->mutex_printf);
}

void	ft_sleep(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_sleep);
	ft_usleep(rules->time_sleep, philo, rules);
}

void	ft_find_fork(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_think);
	
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	while (rules->fork[philo->fork_1] != 0)
	{
		pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
		pthread_mutex_lock(&rules->mutex_died);
		if (ft_time(&philo->last_meal) >=rules->time_die && rules->is_died != 1)
			ft_died(rules, philo);
		pthread_mutex_unlock(&rules->mutex_died);
		// usleep(50);
		pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	}
	rules->fork[philo->fork_1] = 1;
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
	
	ft_printf(rules, philo, e_fork);
	
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_2]);
	while (rules->fork[philo->fork_2] != 0)
	{
		pthread_mutex_unlock(&rules->mutex_fork[philo->fork_2]);
		pthread_mutex_lock(&rules->mutex_died);
		if (ft_time(&philo->last_meal) >=rules->time_die && rules->is_died != 1)
			ft_died(rules, philo);
		pthread_mutex_unlock(&rules->mutex_died);
		// usleep(50);
		pthread_mutex_lock(&rules->mutex_fork[philo->fork_2]);
	}
	rules->fork[philo->fork_2] = 1;
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_2]);
	
	ft_printf(rules, philo, e_fork);
	ft_eat(rules, philo);

	pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	rules->fork[philo->fork_1] = 0;
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_2]);
	rules->fork[philo->fork_2] = 0;
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_2]);
}

void	ft_eat(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_eat);
	gettimeofday(&philo->last_meal, NULL);
	ft_usleep(rules->time_eat, philo, rules);
}
