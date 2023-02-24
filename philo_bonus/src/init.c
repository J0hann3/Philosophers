/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:40:52 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 20:17:08 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_malloc(t_rules *mutex)
{
	mutex->str = malloc(sizeof(char *) * 5);
	// mutex->mutex_fork = malloc(sizeof(pthread_mutex_t) * mutex->number_philo);
	// mutex->fork = malloc(sizeof(int) * mutex->number_philo);
	// mutex->philo_thread = malloc(sizeof(pthread_t) * mutex->number_philo);
	// if (mutex->fork == NULL || mutex->mutex_fork == NULL || mutex->str == NULL
	// 	|| mutex->philo_thread == NULL)
	// {
	// 	free(mutex->str);
	// 	free(mutex->mutex_fork);
	// 	free(mutex->philo_thread);
	// 	free(mutex->fork);
	// 	return (1);
	// }
	memset(mutex->str, 0, sizeof(char *) * 5);
	if (fill_print(mutex->str) == 1)
		return (error(mutex), 1);
	return (0);
}

// int	ft_create_thread(t_rules *mutex)
// {
// 	int	i;

// 	i = 0;
// 	while (i < mutex->number_philo)
// 	{
// 		if (pthread_create(&(mutex->philo_thread[i]), NULL, &philosophers,
// 				(void *)mutex) != 0)
// 		{
// 			printf("Error : Failed to create thread\n");
// 			return (1);
// 		}
// 		++i;
// 	}
// 	return (0);
// }

void	ft_destroy(t_rules *mutex)
{
	// free(mutex->mutex_fork);
	// free(mutex->philo_thread);
	// free(mutex->fork);
	free_str(mutex->str);
}

void	error(t_rules *mutex)
{
	// free(mutex->mutex_fork);
	// free(mutex->philo_thread);
	// free(mutex->fork);
	free_str(mutex->str);
}
