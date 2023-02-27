/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 18:13:54 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/stat.h>

// static void	init_philo()
// {}

void	philosophers(t_rules *rules, int n_philo)
{
	t_philo			philo;
	t_thread_death	death;

	printf("philo	:			%d\n", n_philo + 1);
	philo.sem = sem_open(S_FORK, O_EXCL);
	philo.mutex = sem_open(S_MUTEX, O_EXCL);
	philo.meal = sem_open(S_MEAL, O_EXCL);
	if (philo.meal == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore in philo meal\n");
		return ;
	}
	if (philo.sem == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore in philo fork\n");
		return ;
	}
	if (philo.mutex == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore in philo mutex\n");
		return ;
	}
	philo.nb = n_philo + 1;
	printf("philo	:				%d\n", philo.nb);
	
	philo.last_meal.tv_sec = rules->time_begin.tv_sec;
	philo.last_meal.tv_usec= rules->time_begin.tv_usec;

	if (rules->number_philo % 2 == 0)
		philo.last_action = philo.nb % 2 + 1;
	else
		philo.last_action = philo.nb % 3 + 1;
	death.philo = &philo;
	death.rules = rules;
	pthread_create(&death.thread, NULL, &check_death, (void *)&death);
	pthread_detach(death.thread);
	
	
	if (rules->number_eat == -1)
		infini_time(rules, &philo);
	else
		n_time(rules, &philo);
	
	if (sem_close(philo.sem) < 0 || sem_close(philo.mutex) < 0 ||
		sem_close(philo.meal) < 0)
	{
		printf("Error : Failed to close the semaphore\n");
	}
	return ;
}

int	main(int argc, char **argv)
{
	int			i;
	pid_t		*pid;
	pthread_t	p_check_meal;
	t_rules		mutex;
	sem_t		*s_death;

	if (parsing(argc, argv, &mutex) == -1)
		return (printf("Error : Incorrect arguments\n"), 1);
	if (mutex.number_philo == 0 || mutex.number_eat == 0)
		return (0);
	if (mutex.number_philo % 2 == 0)
		mutex.time_think = 0;
	else
		mutex.time_think = mutex.time_eat;
	pid = ft_init_malloc(&mutex);
	if (pid == NULL)
		return (1);
	gettimeofday(&mutex.time_begin, NULL);

	if (ft_init_semaphore(&mutex) == 1)
		return (1);
	if (pthread_create(&p_check_meal, NULL, &check_meal, (void *)&mutex.number_philo) != 0)
		return (printf("Error : Failed to create thread\n"), 1);
	if (pthread_detach(p_check_meal) != 0)
		return (1);
	if (ft_create_process(&mutex, pid) <= 0)
		return (0);
	s_death = sem_open(S_DEATH, O_EXCL);
	sem_wait(s_death);
	if (sem_close(s_death) < 0)
		return(printf("Error : Failed to close the semaphore\n"), 1);
	i = -1;
	while (++i < mutex.number_philo)
		if (kill(pid[i], SIGKILL) == -1)
			return(printf("Error : Failed to kill process\n"), 1);
	error(&mutex, pid);
	return (0);
}
