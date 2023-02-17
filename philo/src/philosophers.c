/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 18:27:18 by jvigny           ###   ########.fr       */
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
	philo.last_meal.tv_sec = philo_rules->time_begin.tv_sec;
	philo.last_meal.tv_usec= philo_rules->time_begin.tv_usec;
	philo.fork_1 = philo.nb % philo_rules->number_philo;
	philo.fork_2 = philo.nb - 1;
	if (philo.fork_2 < 0)
		philo.fork_2 = philo_rules->number_philo - 1;
	// pthread_mutex_lock(&philo_rules->mutex_printf);
	// printf("philo: %d	fork_1: %d	fork_2: %d\n", philo.nb, philo.fork_1, philo.fork_2);
	// pthread_mutex_unlock(&philo_rules->mutex_printf);
	philo.last_action = philo.nb % 2 + 1;
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

	if (parsing(argc, argv, &mutex) == -1)
		return (write(2, "Error\n",5), 1);
	mutex.index = 0;
	mutex.is_died = 0;
	if (ft_init_malloc(&mutex) == 1)
		return (1);
	memset(mutex.fork, 0, sizeof(int) * mutex.number_philo);
	// i = 0;
	// while (i < mutex.number_philo)
	// {
	// 	printf("fork : %d\n",mutex.fork[i]);
	// 	i++;
	// }
	ft_init_rules(&mutex);
	gettimeofday(&mutex.time_begin, NULL);
	ft_create_thread(&mutex);
	// Wait thread
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_join(mutex.philo[i], NULL);		
		++i;
	}
	ft_destroy(&mutex);
	return (0);
}

/**/