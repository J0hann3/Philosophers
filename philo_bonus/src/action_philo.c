/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 21:14:35 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

static int	find_fork(t_rules *rules, t_philo *philo)
{
	// while (rules->fork[fork] != 0)
	// {
	// 	if (rules->is_died != 1
	// 		&& ft_time(&philo->last_meal, timestamp()) >= rules->time_die)
	// 	{
	// 		ft_died(rules, philo);
	// 		return (-1);
	// 	}
	// }
	// rules->fork[fork] = 1;
	// printf("try fork\n");
	if (sem_wait(philo->sem) < 0)
		printf("rate\n");
	return (0);
}

void	ft_find_fork_eat(t_rules *rules, t_philo *philo)
{
	find_fork(rules, philo);
	ft_printf(rules, philo, e_fork);
	find_fork(rules, philo);
	ft_printf(rules, philo, e_fork);
	ft_eat(rules, philo);
	sem_post(philo->sem);
	sem_post(philo->sem);
}
