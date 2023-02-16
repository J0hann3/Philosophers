/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:40:52 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 17:58:17 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_malloc(t_mutex *mutex)
{
	mutex->str = malloc(sizeof(char *) * 5);
	mutex->mutex_fork = malloc(sizeof(pthread_mutex_t) * mutex->number_philo);
	mutex->philo = malloc(sizeof(pthread_t) * mutex->number_philo);
	mutex->time_begin = malloc(sizeof(struct timeval));
	if (mutex->philo == NULL || mutex->mutex_fork == NULL || mutex->str == NULL || mutex->time_begin == NULL)
	{
		free(mutex->str);
		free(mutex->mutex_fork);
		free(mutex->philo);
		free(mutex->time_begin);
		return (1);
	}
	fill_print(mutex->str);
	return (0);
}

void	ft_init_mutex(t_mutex *mutex)
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
}

void	ft_create_thread(t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < mutex->number_philo)
	{
		pthread_create(&(mutex->philo[i]), NULL, &philosophers, (void *)mutex);
		++i;
	}
}

void	ft_destroy(t_mutex *mutex)
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
	free(mutex->mutex_fork);
	free(mutex->philo);
	free(mutex->time_begin);
	free_str(mutex->str);
}