/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 20:19:04 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static void	init_philo()
// {}

void	philosophers(t_rules *rules, int n_philo)
{
	t_philo		philo;

	philo.sem = sem_open(SEM_NAME, O_EXCL);
	if (philo.sem == SEM_FAILED)
	{
		printf("Error : Failed to create the semaphore\n");
		return ;
	}
	philo.nb = n_philo;
	philo.last_meal.tv_sec = rules->time_begin.tv_sec;
	philo.last_meal.tv_usec= rules->time_begin.tv_usec;
	// philo.fork_1 = philo.nb - 1;
	// philo.fork_2 = philo.nb % rules->number_philo;
	// if (philo.fork_1 == rules->number_philo - 1)
	// {
	// 	philo.fork_1 = philo.nb % rules->number_philo;
	// 	philo.fork_2 = philo.nb - 1;
	// }
	if (rules->number_philo % 2 == 0)
		philo.last_action = philo.nb % 2 + 1;
	else
		philo.last_action = philo.nb % 3 + 1;
	if (rules->number_eat == -1)
		infini_time(rules, &philo);
	else
		n_time(rules, &philo);
	
	if (sem_close(philo.sem) < 0)
	{
		printf("Error : Failed to close the semaphore\n");
	}
	return ;
}

int	main(int argc, char **argv)
{
	int		i;
	int		philo;
	int		pid_child;
	t_rules	mutex;
	sem_t	*semaphore = NULL;

	if (parsing(argc, argv, &mutex) == -1)
	{
		printf("Error : Incorrect arguments\n");
		return (1);
	}
	if (mutex.number_philo == 0 || mutex.number_eat == 0)
		return (0);
	mutex.is_died = 0;
	mutex.n_meal = 0;
	if (mutex.number_philo % 2 == 0)
		mutex.time_think = 0;
	else
		mutex.time_think = mutex.time_eat;
	
	// ------- Semaphore --------
	semaphore = sem_open(SEM_NAME, O_CREAT, 0644, mutex.number_philo);
	if (semaphore == SEM_FAILED)
		return(printf("Error : Failed to create the semaphore\n"), 1);
	if (sem_close(semaphore) < 0)
	{
		sem_unlink(SEM_NAME);
		return(printf("Error : Failed to close the semaphore\n"), 1);
	}
	if (ft_init_malloc(&mutex) == 1)
		return (1);
	gettimeofday(&mutex.time_begin, NULL);

	// ------ Create fork --------
	pid_child = fork();
	i = 1;
	philo = 0;
	while (i < mutex.number_philo)
	{
		if (pid_child == 0)
		{
			pid_child = fork();
			// if (pid_child != 0)
			// 	printf("child  : %d, pere : %u	i:%d\n", getpid(), pid_child, i);
			philo++;
		}
		else
			break;
		++i;
	}
	if (pid_child == 0 && i == mutex.number_philo)
		philo++;
	if (philo != 0)
		philosophers(&mutex, philo);
	waitpid(pid_child, NULL, 0);
	if (philo == 0)
		sem_unlink(SEM_NAME);
	// printf("pid : %d %d %d\n", getpid(), pid_child, philo);
	return (0);
}
