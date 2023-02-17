/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:40:52 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 13:32:53 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_malloc(t_rules *mutex)
{
	mutex->str = malloc(sizeof(char *) * 5);
	mutex->mutex_fork = malloc(sizeof(pthread_mutex_t) * mutex->number_philo);
	mutex->philo = malloc(sizeof(pthread_t) * mutex->number_philo);
	if (mutex->philo == NULL || mutex->mutex_fork == NULL || mutex->str == NULL)
	{
		free(mutex->str);
		free(mutex->mutex_fork);
		free(mutex->philo);
		return (1);
	}
	fill_print(mutex->str);
	return (0);
}

void	ft_init_rules(t_rules *mutex)
{
	int	i;

	i = 0;
	while (i < mutex->number_philo)
	{
		pthread_mutex_init(&mutex->mutex_fork[i], NULL);
		++i;
	}
	pthread_mutex_init(&mutex->mutex_printf, NULL);
	pthread_mutex_init(&mutex->mutex_index, NULL);
	pthread_mutex_init(&mutex->mutex_died, NULL);
}

void	ft_create_thread(t_rules *mutex)
{
	int	i;

	i = 0;
	while (i < mutex->number_philo)
	{
		pthread_create(&(mutex->philo[i]), NULL, &philosophers, (void *)mutex);
		++i;
	}
}

void	ft_destroy(t_rules *mutex)
{
	int	i;
	
	i = 0;
	while (i < mutex->number_philo)
	{
		pthread_mutex_destroy(&mutex->mutex_fork[i]);
		++i;
	}
	pthread_mutex_destroy(&mutex->mutex_printf);
	pthread_mutex_destroy(&mutex->mutex_index);
	pthread_mutex_destroy(&mutex->mutex_died);
	free(mutex->mutex_fork);
	free(mutex->philo);
	free_str(mutex->str);
}