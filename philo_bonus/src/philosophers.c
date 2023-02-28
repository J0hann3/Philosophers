/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/28 17:38:19 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philosophers(t_rules *rules, int n_philo)
{
	t_philo			philo;
	t_thread_death	death;
	char			*name_sem;
	char			*name;

	philo.nb = n_philo + 1;
	name = ft_itoa(philo.nb);
	name_sem = ft_strjoin("/meal", name);
	sem_unlink(name_sem);
	philo.mutex_meal = sem_open(name_sem, O_CREAT, 0644, 1);
	free(name_sem);
	free(name);
	philo.meal = sem_open(S_MEAL, O_EXCL);
	philo.sem = sem_open(S_FORK, O_EXCL);
	philo.mutex = sem_open(S_MUTEX, O_EXCL);
	philo.death = sem_open(S_DEATH, O_EXCL);
	if (philo.meal == SEM_FAILED || philo.death == SEM_FAILED || philo.mutex == SEM_FAILED ||
		philo.sem == SEM_FAILED || philo.mutex_meal == SEM_FAILED)
	{
		printf("Error : Failed to create the semaphore\n");
		exit(EXIT_FAILURE);				//don't stop the other philo
	}
	
	philo.last_meal.tv_sec = rules->time_begin.tv_sec;
	philo.last_meal.tv_usec= rules->time_begin.tv_usec;

	if (rules->number_philo % 2 == 0)
		philo.last_action = philo.nb % 2 + 1;
	else
		philo.last_action = philo.nb % 3 + 1;
	death.philo = &philo;
	death.rules = rules;
	if (pthread_create(&death.thread, NULL, &check_death, (void *)&death) != 0)
	{
		printf("Error : Failed to create thread\n");
		return ;
	}
	if (pthread_detach(death.thread) != 0)
	{
		printf("Error : Failed to create thread\n");
		return ;
	}
	
	if (rules->number_eat == -1)
		infini_time(rules, &philo);
	else
		n_time(rules, &philo);
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
		return (printf("Error : Failed to allocated memory\n"), 1);
	gettimeofday(&mutex.time_begin, NULL);

	ft_init_semaphore(&mutex, &sem, pid);
	sem.nb_philo = mutex.number_philo;
	
	if (mutex.number_eat != -1 && pthread_create(&p_check_meal, NULL,
			&check_meal, (void *)&sem) != 0)
		return (printf("Error : Failed to create thread\n"), error(&mutex, pid, 0), 1);
	if (ft_create_process(&mutex, pid) <= 0)
		return (0);
	
	sem_wait(sem.death);
	
	i = -1;
	while (++i < mutex.number_philo)
		if (kill(pid[i], SIGKILL) == -1)
			return(printf("Error : Failed to kill process\n"), error(&mutex, pid, 0), 1);
	i = 0;
	while (i < sem.nb_philo)
	{
		sem_post(sem.meal);
		++i;
	}
	if (mutex.number_eat != -1 && pthread_join(p_check_meal, NULL) != 0)
		return (printf("Error : Failed to deatch thread\n"), error(&mutex, pid, 0), 1);
	ft_close_sem(&sem, &mutex, pid);
	return (0);
}
