/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:40:52 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/28 16:59:54 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pid_t	*ft_init_malloc(t_rules *mutex)
{
	pid_t	*pid;
	mutex->str = malloc(sizeof(char *) * 5);
	pid = malloc(sizeof(pid_t) * mutex->number_philo);
	if (pid == NULL || mutex->str == NULL)
		return (error(mutex, pid, 1), NULL);
	memset(pid, 0, sizeof(pid_t) * mutex->number_philo);
	memset(mutex->str, 0, sizeof(char *) * 5);
	if (fill_print(mutex->str) == 1)
		return (error(mutex, pid, 0), NULL);
	return (pid);
}

void	ft_init_semaphore(t_rules *rules, t_semaphore *sem, pid_t *pid)
{
	sem_unlink(S_FORK);
	sem_unlink(S_DEATH);
	sem_unlink(S_MUTEX);
	sem_unlink(S_MEAL);
	sem->fork = sem_open(S_FORK, O_CREAT, 0644, rules->number_philo);
	sem->death = sem_open(S_DEATH, O_CREAT, 0644, 0);
	sem->mutex = sem_open(S_MUTEX, O_CREAT, 0644, 1);
	sem->meal = sem_open(S_MEAL, O_CREAT, 0644, 0);
	if (sem->fork == SEM_FAILED || sem->death == SEM_FAILED || sem->mutex == SEM_FAILED ||
		sem->meal == SEM_FAILED)
	{
		printf("Error : Failed to create the semaphore\n");
		error(rules, pid, 0);
		exit(EXIT_FAILURE);
	}
}

int	ft_create_process(t_rules *rules, pid_t *pid)
{
	int	i;
	pid_t pid_child;

	i = 0;
	while (i < rules->number_philo)
	{
		pid_child = fork();
		if (pid_child == -1)
		{
			i = -1;
			while (++i < rules->number_philo)
				kill(pid[i], SIGKILL);
			return (printf("Error : Failed to create process\n"), error(rules, pid, 0), -1);
		}
		else if (pid_child != 0)
			pid[i] = pid_child;
		else
		{
			philosophers(rules, i);
			return (0);
		}
		++i;
	}
	return (1);
}

int	ft_close_sem(t_semaphore *sem, t_rules *rules, pid_t *pid)
{
	if (sem_close(sem->fork) < 0)
		return(printf("Error : Failed to close the semaphore\n"), error(rules, pid, 0), 1);
	if (sem_close(sem->meal) < 0)
		return(printf("Error : Failed to close the semaphore\n"), error(rules, pid, 0), 1);
	if (sem_close(sem->mutex) < 0)
		return(printf("Error : Failed to close the semaphore\n"), error(rules, pid, 0), 1);
	if (sem_close(sem->death) < 0)
		return(printf("Error : Failed to close the semaphore\n"), error(rules, pid, 0), 1);
	error(rules, pid, 0);
	return (0);
}

void	error(t_rules *mutex, pid_t *pid, short boolean)
{
	if (boolean == 1)
		free(mutex->str);
	else
		free_str(mutex->str);
	free(pid);
	sem_unlink(S_FORK);	
	sem_unlink(S_DEATH);
	sem_unlink(S_MUTEX);
	sem_unlink(S_MEAL);
}
