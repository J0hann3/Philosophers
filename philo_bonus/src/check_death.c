/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:06:14 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 15:38:22 by jvigny           ###   ########.fr       */
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
			// printf("meurt--------------%d\n", death->philo->nb);
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

// void	*check_meal(void *arg)
// {
// 	sem_t	*s_meal;
// 	sem_t	*s_mutex;
// 	int		i;

// 	*s_meal = sem_open(S_MEAL, O_CREAT, 0644, rules->number_philo);
// 	*s_mutex = sem_open(S_MEAL, O_EXCL);
	

// 	//	Stop simulation
// 	sem_wait(s_mutex);
// 	i = -1;
// 	while (++i < mutex.number_philo)
// 	{
// 		kill(pid[i], SIGKILL);
// 	}
// }