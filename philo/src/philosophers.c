/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 13:31:53 by jvigny           ###   ########.fr       */
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
	// Malloc
	mutex.str = malloc(sizeof(char *) * 5);
	mutex.mutex_fork = malloc(sizeof(pthread_mutex_t) * mutex.number_philo);
	mutex.philo = malloc(sizeof(pthread_mutex_t) * mutex.number_philo);
	mutex.time_begin = malloc(sizeof(struct timeval));
	if (mutex.philo == NULL || mutex.mutex_fork == NULL || mutex.str == NULL || mutex.time_begin == NULL)
	{
		free(mutex.str);
		free(mutex.mutex_fork);
		free(mutex.philo);
		free(mutex.time_begin);
		return (1);
	}
	fill_print(mutex.str);
	// Init Mutex
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_mutex_init(&mutex.mutex_fork[i], NULL);
		++i;
	}
	pthread_mutex_init(&mutex.mutex_printf, NULL);
	pthread_mutex_init(&mutex.mutex_index, NULL);
	// Create thread
	gettimeofday(mutex.time_begin, NULL);
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_create(&(mutex.philo[i]), NULL, philosophers, (void *)&mutex);
		++i;
	}
	// Wait thread
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_join(mutex.philo[i], NULL);
		++i;
	}
	// Destroy Mutex
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_mutex_destroy(&mutex.mutex_fork[i]);
		++i;
	}
	pthread_mutex_destroy(&mutex.mutex_printf);
	pthread_mutex_destroy(&mutex.mutex_index);
	free(mutex.mutex_fork);
	free(mutex.philo);
	free(mutex.time_begin);
	free_str(mutex.str);
	return (0);
}

/**/