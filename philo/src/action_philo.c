/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/22 13:21:07 by jvigny           ###   ########.fr       */
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

void	ft_died(t_rules *rules, t_philo *philo)
{
	rules->is_died = 1;
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s\n",ft_time(&rules->time_begin, timestamp()), philo->nb, rules->str[e_die]);
	pthread_mutex_unlock(&rules->mutex_printf);
}

void	ft_sleep(t_rules *rules, t_philo *philo)
{
	struct timeval	now;
	
	now = ft_printf(rules, philo, e_sleep);
	// printf("s : %ld,	us: %ld\n", now.tv_sec, now.tv_usec);
	ft_usleep(now, rules->time_sleep, philo, rules);
}

void	ft_think(t_rules *rules, t_philo *philo)
{
	struct timeval	now;
	
	now = ft_printf(rules, philo, e_think);
	ft_usleep(now, rules->time_think, philo, rules);
}

void	ft_find_fork(t_rules *rules, t_philo *philo)
{
	// struct timeval	time;
	
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	while (rules->fork[philo->fork_1] != 0)
	{
		pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
		pthread_mutex_lock(&rules->mutex_died);
		if (rules->is_died != 1 && ft_time(&philo->last_meal, timestamp()) >= rules->time_die)
		{
			ft_died(rules, philo);
			pthread_mutex_unlock(&rules->mutex_died);
			return ;
		}
		pthread_mutex_unlock(&rules->mutex_died);
		// usleep(50);
		pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	}
	rules->fork[philo->fork_1] = 1;
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
	
	ft_printf(rules, philo, e_fork);
	// if (philo->fork_1 == philo->fork_2)
	// {
	// 	ft_usleep(time, rules->time_die + 10, philo, rules);
	// 	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
	// 	return ;	
	// }

	pthread_mutex_lock(&rules->mutex_fork[philo->fork_2]);
	while (rules->fork[philo->fork_2] != 0)
	{
		pthread_mutex_unlock(&rules->mutex_fork[philo->fork_2]);
		pthread_mutex_lock(&rules->mutex_died);
		if (rules->is_died != 1 && ft_time(&philo->last_meal, timestamp()) >= rules->time_die)
		{
			pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
			rules->fork[philo->fork_1] = 0;
			pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
			ft_died(rules, philo);
			pthread_mutex_unlock(&rules->mutex_died);
			return ;
		}
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
	struct timeval	now;
	
	now = ft_printf(rules, philo, e_eat);
	philo->last_meal.tv_sec = now.tv_sec;
	philo->last_meal.tv_usec = now.tv_usec;
	ft_usleep(now, rules->time_eat, philo, rules);
}
