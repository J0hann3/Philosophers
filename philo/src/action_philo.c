/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/06/03 18:52:50 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_rules *rules, t_philo *philo)
{
	struct timeval	now;

	now = ft_printf(rules, philo, e_eat);
	philo->last_meal.tv_sec = now.tv_sec;
	philo->last_meal.tv_usec = now.tv_usec;
	ft_usleep(now, rules->time_eat, philo, rules);
}

void	ft_sleep(t_rules *rules, t_philo *philo)
{
	struct timeval	now;

	now = ft_printf(rules, philo, e_sleep);
	ft_usleep(now, rules->time_sleep, philo, rules);
}

void	ft_think(t_rules *rules, t_philo *philo)
{
	struct timeval	now;

	now = ft_printf(rules, philo, e_think);
	ft_usleep(now, rules->time_think, philo, rules);
}

static int	find_fork(t_rules *rules, t_philo *philo, int fork)
{
	pthread_mutex_lock(&rules->mutex_fork[fork]);
	while (rules->fork[fork] != 0)
	{
		pthread_mutex_unlock(&rules->mutex_fork[fork]);
		pthread_mutex_lock(&rules->mutex_died);
		if (rules->is_died != 1
			&& ft_time(&philo->last_meal, timestamp()) >= rules->time_die)
		{
			ft_died(rules, philo);
			pthread_mutex_unlock(&rules->mutex_died);
			return (-1);
		}
		pthread_mutex_unlock(&rules->mutex_died);
		usleep(100);
		pthread_mutex_lock(&rules->mutex_fork[fork]);
	}
	rules->fork[fork] = 1;
	pthread_mutex_unlock(&rules->mutex_fork[fork]);
	return (0);
}

void	ft_find_fork_eat(t_rules *rules, t_philo *philo)
{
	if (find_fork(rules, philo, philo->fork_1) == -1)
		return ;
	ft_printf(rules, philo, e_fork);
	if (find_fork(rules, philo, philo->fork_2) == -1)
	{
		pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
		rules->fork[philo->fork_1] = 0;
		pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
		return ;
	}
	ft_printf(rules, philo, e_fork);
	ft_eat(rules, philo);
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	rules->fork[philo->fork_1] = 0;
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_2]);
	rules->fork[philo->fork_2] = 0;
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_2]);
}
