/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 20:48:05 by jvigny           ###   ########.fr       */
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

	philo.meal = sem_open(S_MEAL, O_EXCL);
	if (philo.meal == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore in philo meal\n");
		return ;
	}
	philo.sem = sem_open(S_FORK, O_EXCL);
	if (philo.sem == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore in philo fork\n");
		return ;
	}
	philo.mutex = sem_open(S_MUTEX, O_EXCL);
	if (philo.mutex == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore in philo mutex\n");
		return ;
	}
	philo.death = sem_open(S_DEATH, O_EXCL);
	if (philo.death == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore in philo mutex\n");
		return ;
	}
	philo.nb = n_philo + 1;
	
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
	return ;
}

int	main(int argc, char **argv)
{
	int			i;
	pid_t		*pid;
	pthread_t	p_check_meal;
	t_rules		mutex;
	t_semaphore	sem;

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

	if (ft_init_semaphore(&mutex, &sem) == 1)
		return (1);
	sem.nb_philo = mutex.number_philo;
	if (pthread_create(&p_check_meal, NULL, &check_meal, (void *)&sem) != 0)
		return (printf("Error : Failed to create thread\n"), 1);
	if (pthread_detach(p_check_meal) != 0)
		return (1);
	if (ft_create_process(&mutex, pid) <= 0)
		return (0);
	sem_wait(sem.death);
	i = -1;
	while (++i < mutex.number_philo)
		if (kill(pid[i], SIGKILL) == -1)
			return(printf("Error : Failed to kill process\n"), 1);
	//-----Close semaphore-----
	if (sem_close(sem.fork) < 0)
		return(printf("Error : Failed to close the semaphore\n"), 1);
	if (sem_close(sem.meal) < 0)
		return(printf("Error : Failed to close the semaphore\n"), 1);
	if (sem_close(sem.mutex) < 0)
		return(printf("Error : Failed to close the semaphore\n"), 1);
	if (sem_close(sem.death) < 0)
		return(printf("Error : Failed to close the semaphore\n"), 1);
	error(&mutex, pid);
	return (0);
}
