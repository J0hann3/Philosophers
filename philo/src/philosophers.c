/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 17:57:00 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*\*/
void	*philosophers(void	*p)
{
	t_mutex *philo;
	int				nb;

	philo = (t_mutex *)p;
	pthread_mutex_lock(&philo->mutex_index);
	(philo->index)++;
	nb = philo->index;
	pthread_mutex_unlock(&philo->mutex_index);
	// printf("time : %ld\n", (philo->time_begin)->tv_usec / 1000 + (philo->time_begin)->tv_sec * 1000);
	if (philo->number_eat == -1)
		infini_time(philo, nb);
	else
		n_time(philo, nb);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i;
	t_mutex			mutex;

	if (parsing(argc, argv, &mutex) == -1)
		return (write(2, "Error\n",5), 1);
	mutex.index = 0;
	ft_init_malloc(&mutex);
	ft_init_mutex(&mutex);
	gettimeofday(mutex.time_begin, NULL);
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