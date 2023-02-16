/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 19:38:05 by jvigny           ###   ########.fr       */
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
	philo->is_died = 1;
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s\n",ft_time(rules->time_begin), philo->nb, rules->str[e_die]);
	pthread_mutex_unlock(&rules->mutex_printf);
}

void	ft_think(t_rules *rules, t_philo *philo)
{
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s\n",ft_time(rules->time_begin), philo->nb, rules->str[e_think]);
	pthread_mutex_unlock(&rules->mutex_printf);
}

void	ft_sleep(t_rules *rules, t_philo *philo)
{
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s\n",ft_time(rules->time_begin), philo->nb, rules->str[e_sleep]);
	pthread_mutex_unlock(&rules->mutex_printf);
	ft_usleep(rules->time_sleep, philo, rules);
}

void	ft_find_fork(t_rules *rules, t_philo *philo)
{
	ft_think(rules, philo);
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_1]);
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s left : %d\n", ft_time(rules->time_begin), philo->nb, rules->str[e_fork], philo->fork_1);
	pthread_mutex_unlock(&rules->mutex_printf);
	pthread_mutex_lock(&rules->mutex_fork[philo->fork_2]);
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s right : %d\n", ft_time(rules->time_begin), philo->nb, rules->str[e_fork], philo->fork_2);
	pthread_mutex_unlock(&rules->mutex_printf);
	ft_eat(rules, philo);
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_1]);
	pthread_mutex_unlock(&rules->mutex_fork[philo->fork_2]);
}

void	ft_eat(t_rules *rules, t_philo *philo)
{
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s\n",ft_time(rules->time_begin), philo->nb, rules->str[e_eat]);
	printf("%ld %ld\n", time_conv(philo->last_meal), time_conv(rules->time_begin));
	pthread_mutex_unlock(&rules->mutex_printf);
	gettimeofday(philo->last_meal, NULL);
	ft_usleep(rules->time_eat, philo, rules);
}
