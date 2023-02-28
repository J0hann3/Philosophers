/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:06:14 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/28 17:00:08 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_death(void *arg)
{
	t_thread_death	*death;
	
	death = (t_thread_death *)arg;
	while (1)
	{
		if (death->rules->time_die <= ft_time(&death->philo->last_meal,
			timestamp()))
		{
			sem_wait(death->philo->mutex);
			sem_post(death->philo->death);
			printf("%ld %d %s\n",ft_time(&death->rules->time_begin, timestamp()),
				death->philo->nb, death->rules->str[e_die]);
			sem_close(death->philo->death);
			sem_close(death->philo->mutex);
			return (death);
		}
		usleep(10);
	}
}

void	*check_meal(void *arg)
{
	t_semaphore	*sem;
	int			i;

	sem = (t_semaphore *)arg;
	i = 0;
	while (i < sem->nb_philo)
	{
		sem_wait(sem->meal);
		++i;
	}
	//	Stop simulation
	// printf("test---------------\n");
	// sem_wait(sem->mutex);
	// printf("test---------------\n");
	sem_post(sem->death);
	// printf("test---------------\n");
	return (NULL);
}
