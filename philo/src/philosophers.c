/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/13 14:33:45 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*\*/
void	*philosophers(void	*p)
{
	t_mutex *philo;
	struct timeval	last_meal;

	philo = (t_mutex *)p;
	if (gettimeofday(&last_meal, NULL) != 0)
	philo = (t_mutex *)p;
	printf("CREATE PHILO\n");
	// Eat
	usleep(philo->time_eat);
	// Think

	// Sleep
	usleep(philo->time_sleep);
	return (p);
}

int	main(int argc, char **argv)
{
	int				i;
	t_mutex			mutex;
	char			**str;

	if (parsing(argc, argv, &mutex) == -1)
		return (write(2, "Error\n",5), 1);
	// Malloc
	str = malloc(sizeof(char *) * 5);
	mutex.mutex_fork = malloc(sizeof(pthread_mutex_t) * mutex.number_philo);
	mutex.philo = malloc(sizeof(pthread_mutex_t) * mutex.number_philo);
	if (mutex.philo == NULL || mutex.mutex_fork == NULL || str == NULL)
	{
		free(str);
		free(mutex.mutex_fork);
		free(mutex.philo);
		return (1);
	}
	fill_print(str);
	// Init Mutex
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_mutex_init(&mutex.mutex_fork[i], NULL);
		++i;
	}
	pthread_mutex_init(&mutex.mutex_printf, NULL);
	// Create thread
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_create(&(mutex.philo[i]), NULL, philosophers, (void *)&(mutex));
		++i;
	}
	// Wait thread
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_join(mutex.philo[i], NULL);
		printf("KILL PHILO\n");
		++i;
	}
	// Destroy Mutex
	i = 0;
	while (i < mutex.number_philo)
	{
		pthread_mutex_destroy(&mutex.mutex_fork[i]);
		++i;
	}
	return (0);
}

/**/