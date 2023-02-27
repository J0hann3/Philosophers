/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:36:53 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 17:17:29 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat(t_rules *rules, t_philo *philo)
{
	struct timeval	now;

	now = ft_printf(rules, philo, e_eat);
	philo->last_meal.tv_sec = now.tv_sec;
	philo->last_meal.tv_usec = now.tv_usec;
	usleep(rules->time_eat * 1000);
}

void	ft_sleep(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_sleep);
	usleep(rules->time_sleep * 1000);
}

void	ft_think(t_rules *rules, t_philo *philo)
{
	ft_printf(rules, philo, e_think);
	usleep(rules->time_think * 1000);
}

void	ft_find_fork_eat(t_rules *rules, t_philo *philo)
{
	sem_wait(philo->sem);
	ft_printf(rules, philo, e_fork);
	sem_wait(philo->sem);
	ft_printf(rules, philo, e_fork);
	ft_eat(rules, philo);
	sem_post(philo->sem);
	sem_post(philo->sem);
}
