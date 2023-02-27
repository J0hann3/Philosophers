/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:06:14 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 18:08:27 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_death(void *arg)
{
	t_thread_death	*death;
	sem_t			*s_death;
	sem_t			*s_mutex;

	death = (t_thread_death *)arg;
	s_death = sem_open(S_DEATH, O_EXCL);
	s_mutex = sem_open(S_MUTEX, O_EXCL);
	if (s_death == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore\n");
		return (s_death);	//should kill all the philo
	}
	while (1)
	{
		if (death->rules->time_die <= ft_time(&death->philo->last_meal,
			timestamp()))
		{
			sem_wait(s_mutex);
			sem_post(s_death);
			printf("%ld %d %s\n",ft_time(&death->rules->time_begin, timestamp()),
				death->philo->nb, death->rules->str[e_die]);
			sem_close(s_death);
			sem_close(s_mutex);
			return (death);
		}
		usleep(10);
	}
}

void	*check_meal(void *arg)
{
	int		nb_philo;
	sem_t	*s_meal;
	sem_t	*s_mutex;
	sem_t	*s_death;
	int		i;

	nb_philo = *(int *)arg;
	s_meal = sem_open(S_MEAL, O_EXCL);
	s_mutex = sem_open(S_MUTEX, O_EXCL);
	s_death = sem_open(S_DEATH, O_EXCL);
	if (s_meal == SEM_FAILED || s_mutex == SEM_FAILED ||
		s_death == SEM_FAILED)
	{
		sem_close(s_meal);
		sem_close(s_mutex);
		sem_close(s_death);
		printf("Error : Failed to open the semaphore\n");
		return (NULL);
	}
	i = 0;
	while (i < nb_philo)
	{
		sem_wait(s_meal);
		++i;
	}
	sem_close(s_meal);
	//	Stop simulation
	sem_wait(s_mutex);
	sem_post(s_death);
	sem_close(s_mutex);
	sem_close(s_death);
	return (NULL);
}