/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/07/28 16:09:38 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	error(t_rules *mutex)
{
	free(mutex->mutex_fork);
	free(mutex->philo_thread);
	free(mutex->fork);
	free_str(mutex->str);
}

static void	init_philo(t_rules *philo_rules, t_philo *philo)
{
	philo->last_meal.tv_sec = philo_rules->time_begin.tv_sec;
	philo->last_meal.tv_usec = philo_rules->time_begin.tv_usec;
	philo->fork_1 = philo->nb - 1;
	philo->fork_2 = philo->nb % philo_rules->number_philo;
	if (philo->fork_1 == philo_rules->number_philo - 1)
	{
		philo->fork_1 = philo->nb % philo_rules->number_philo;
		philo->fork_2 = philo->nb - 1;
	}
	if (philo_rules->number_philo % 2 == 0)
		philo->last_action = philo->nb % 2;
	else
	{
		philo->last_action = philo->nb % 3;
		if (philo->last_action == e_think)
			usleep(1000);
	}

		
}

void	*philosophers(void	*args)
{
	t_rules		*philo_rules;
	t_philo		philo;

	philo_rules = (t_rules *)args;
	pthread_mutex_lock(&philo_rules->mutex_index);
	(philo_rules->index)++;
	philo.nb = philo_rules->index;
	pthread_mutex_unlock(&philo_rules->mutex_index);
	init_philo(philo_rules, &philo);
	if (philo_rules->number_eat == -1)
		infini_time(philo_rules, &philo);
	else
		n_time(philo_rules, &philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules			mutex;

	if (parsing(argc, argv, &mutex) == -1)
		return (printf("Error : Incorrect arguments\n"), 1);
	if (mutex.number_eat == 0)
		return (0);
	mutex.index = 0;
	mutex.is_died = 0;
	mutex.n_meal = 0;
	// if (mutex.number_philo % 2 == 0)
	mutex.time_think = 0;
	// else
	// 	mutex.time_think = mutex.time_eat;
	if (ft_init_malloc(&mutex) == 1)
		return (1);
	memset(mutex.fork, 0, sizeof(int) * mutex.number_philo);
	if (ft_init_rules(&mutex) == 1)
		return (error(&mutex), 1);
	gettimeofday(&mutex.time_begin, NULL);
	if (ft_create_thread(&mutex) == 1)
		return (error(&mutex), 1);
	ft_join_thread(&mutex);
	ft_destroy(&mutex);
	return (0);
}
