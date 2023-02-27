/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 13:20:07 by jvigny           ###   ########.fr       */
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

	philo.sem = sem_open(S_FORK, O_EXCL);
	if (philo.sem == SEM_FAILED)
	{
		printf("Error : Failed to open the semaphore\n");
		return ;
	}
	philo.nb = n_philo + 1;
	philo.is_dead = 0;
	
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
	// else
	// 	n_time(rules, &philo);
	
	if (sem_close(philo.sem) < 0)
	{
		printf("Error : Failed to close the semaphore\n");
	}
	return ;
}

int	main(int argc, char **argv)
{
	int		i;
	int		pid_child;
	pid_t	*pid;
	t_rules	mutex;
	sem_t	*s_fork = NULL;
	sem_t	*s_death = NULL;

	if (parsing(argc, argv, &mutex) == -1)
	{
		printf("Error : Incorrect arguments\n");
		return (1);
	}
	if (mutex.number_philo == 0 || mutex.number_eat == 0)
		return (0);

	if (mutex.number_philo % 2 == 0)
		mutex.time_think = 0;
	else
		mutex.time_think = mutex.time_eat;
	
	// ------- Semaphore --------
	sem_unlink(S_FORK);
	sem_unlink(S_DEATH);
	s_fork = sem_open(S_FORK, O_CREAT, 0644, mutex.number_philo);
	s_death = sem_open(S_DEATH, O_CREAT, 0644, 0);
	if (s_fork == SEM_FAILED || s_death == SEM_FAILED)
		return(printf("Error : Failed to create the semaphore\n"), 1);
	if (sem_close(s_fork) < 0)
	{
		sem_unlink(S_FORK);
		sem_unlink(S_DEATH);
		return(printf("Error : Failed to close the semaphore\n"), 1);
	}
	// -------- INIT ----------
	pid = ft_init_malloc(&mutex);
	if (pid == NULL)
		return (1);
	gettimeofday(&mutex.time_begin, NULL);

	// ------ Create fork --------
	i = 0;
	// int	pid_main = getpid();
	// printf("main %d\n", pid_main);
	while (i < mutex.number_philo)
	{
		pid_child = fork();
		if (pid_child != 0)
			pid[i] = pid_child;
		else
		{
			philosophers(&mutex, i);
			return (0);
		}
		++i;
	}
	sem_wait(s_death);
	printf("%ld %d %s\n",ft_time(&mutex.time_begin, timestamp()),
			i, mutex.str[e_die]);			// need to keep the number of philo who died
	i = -1;
	while (++i < mutex.number_philo)
		kill(pid[i], SIGKILL);
	if (sem_close(s_death) < 0)
	{
		sem_unlink(S_FORK);	
		sem_unlink(S_DEATH);
		return(printf("Error : Failed to close the semaphore\n"), 1);
	}
	error(&mutex, pid);
	sem_unlink(S_FORK);	
	sem_unlink(S_DEATH);	
	return (0);
}
