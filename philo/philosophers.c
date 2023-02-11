/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/11 18:52:56 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosophers(void	*p)
{
	// t_mutex	*test = (t_mutex *)p;

	pthread_mutex_lock(&((t_mutex *)p)->mutex);
	printf("CREATE THREAD, COUNT : %d\n", ((t_mutex *)p)->count);
	pthread_mutex_unlock(&((t_mutex *)p)->mutex);
	usleep(200);
	pthread_mutex_lock(&((t_mutex *)p)->mutex);
	((t_mutex *)p)->count = ((t_mutex *)p)->count + 200;
	printf("FINISH SLEEP, COUNT : %d\n", (((t_mutex *)p)->count));
	pthread_mutex_unlock(&((t_mutex *)p)->mutex);
	return (p);
}

int	main(int argc, char **argv)
{
	int				i;
	pthread_t		philo[3];
	t_mutex			mutex;
	void			*res;

	(void)argc;
	(void)argv;
	mutex.count = 0;
	i = 0;
	pthread_mutex_init(&mutex.mutex, NULL);
	printf("Before Thread\n");
	while (i < 3)
	{
		pthread_create(&(philo[i]), NULL, philosophers, (void *)&(mutex));
		++i;
	}
	i = 0;
	while (i < 3)
	{
		pthread_join(philo[i], &res);
		pthread_mutex_lock(&((t_mutex *)res)->mutex);
		printf("DELETE THREAD, return value : %d\n", *(int *)res);
		pthread_mutex_unlock(&((t_mutex *)res)->mutex);
		++i;
	}
	printf("After Thread\n");
	pthread_mutex_destroy(&mutex.mutex);
	return (0);
}
