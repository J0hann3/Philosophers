/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:06:14 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 13:19:37 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_death(void *arg)
{
	t_thread_death	*death;
	sem_t			*s_death;

	death = (t_thread_death *)arg;
	s_death = sem_open(S_DEATH, O_EXCL);
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
			death->philo->is_dead = 1;
			sem_post(s_death);
			sem_close(s_death);
			return (death);
		}
		usleep(10);
	}
}