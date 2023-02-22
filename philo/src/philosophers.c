/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/22 13:14:16 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*\*/
void	*philosophers(void	*args)
{
	t_rules		*philo_rules;
	t_philo		philo;

	philo_rules = (t_rules *)args;
	pthread_mutex_lock(&philo_rules->mutex_index);
	(philo_rules->index)++;
	philo.nb = philo_rules->index;
	pthread_mutex_unlock(&philo_rules->mutex_index);
	// philo_rules->philo[philo.nb - 1] = &philo;
	// ---- Init Philo -----
	philo.last_meal.tv_sec = philo_rules->time_begin.tv_sec;
	philo.last_meal.tv_usec= philo_rules->time_begin.tv_usec;
	philo.fork_1 = philo.nb - 1;
	philo.fork_2 = philo.nb % philo_rules->number_philo;
	if (philo.fork_1 == philo_rules->number_philo - 1)
	{
		philo.fork_1 = philo.nb % philo_rules->number_philo;
		philo.fork_2 = philo.nb - 1;
	}
	if (philo_rules->number_philo % 2 == 0)
	{
		philo.last_action = philo.nb % 2 + 1;
		printf("Pair	nb : %d		action : %s\n", philo.nb, philo_rules->str[philo.last_action]);
	}
	else
	{
		philo.last_action = philo.nb % 3 + 1;
		printf("Impair	nb : %d		action : %s\n", philo.nb, philo_rules->str[philo.last_action]);
	}
	// if (philo.nb == philo_rules->number_philo)
	// {
	// 	pthread_mutex_lock(&philo_rules->mutex_died);
	// 	philo_rules->is_died = 0;
	// 	pthread_mutex_unlock(&philo_rules->mutex_died);
	// }
	if (philo_rules->number_eat == -1)
		infini_time(philo_rules, &philo);
	else
		n_time(philo_rules, &philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i;
	t_rules			mutex;

	i = 0;
	if (parsing(argc, argv, &mutex) == -1)
	{
		printf("Error : Incorrect arguments\n");
		return (1);
	}
	mutex.index = 0;
	mutex.is_died = 0;
	if (mutex.number_philo % 2 == 0)
		mutex.time_think = 0;
	else
		mutex.time_think = mutex.time_eat;
	if (ft_init_malloc(&mutex) == 1)
		return (1);
	memset(mutex.fork, 0, sizeof(int) * mutex.number_philo);
	if (ft_init_rules(&mutex) == 1)
		return (error(&mutex), 1);
	gettimeofday(&mutex.time_begin, NULL);
	if (ft_create_thread(&mutex) == 1)
		return (error(&mutex), 1);
	while (i < mutex.number_philo)
	{
		if (pthread_join(mutex.philo_thread[i], NULL) != 0)
		{
			printf("Error : Failed to join thread\n");
			return (error(&mutex), 1);
		}
		++i;
	}
	ft_destroy(&mutex);
	return (0);
}

/**/