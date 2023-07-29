/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:06:14 by jvigny            #+#    #+#             */
/*   Updated: 2023/07/29 16:26:24 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_death(void *arg)
{
	t_thread_death	*death;

	death = (t_thread_death *)arg;
	while (1)
	{
		sem_wait(death->philo->mutex_meal);
		if (death->rules->time_die <= ft_time(&death->philo->last_meal,
				timestamp()))
		{
			sem_post(death->philo->mutex_meal);
			sem_wait(death->philo->mutex);
			sem_post(death->philo->death);
			fprintf(fd, "%ld %d %s\n", ft_time(&death->rules->time_begin,
					timestamp()), death->philo->nb, death->rules->str[e_die]);
			fflush(fd);
			fclose(fd);
			sem_close(death->philo->death);
			sem_close(death->philo->mutex);
			sem_close(death->philo->mutex_meal);
			return (death);
		}
		sem_post(death->philo->mutex_meal);
		usleep(100);
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
	sem_post(sem->death);
	return (NULL);
}
