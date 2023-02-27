/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:40:52 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 15:24:16 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pid_t	*ft_init_malloc(t_rules *mutex)
{
	pid_t	*pid;

	mutex->str = malloc(sizeof(char *) * 5);
	pid = malloc(sizeof(pid_t) * mutex->number_philo);
	if (pid == NULL || mutex->str == NULL)
		return (error(mutex, pid), NULL);
	memset(mutex->str, 0, sizeof(char *) * 5);
	if (fill_print(mutex->str) == 1)
		return (error(mutex, pid), NULL);
	return (pid);
}

int	ft_init_semaphore(sem_t **s_fork, sem_t **s_death, sem_t **s_mutex_death, t_rules *rules)
{
	sem_unlink(S_FORK);
	sem_unlink(S_DEATH);
	sem_unlink(S_MUTEX);
	*s_fork = sem_open(S_FORK, O_CREAT, 0644, rules->number_philo);
	*s_death = sem_open(S_DEATH, O_CREAT, 0644, 0);
	*s_mutex_death = sem_open(S_MUTEX, O_CREAT, 0644, 1);
	if (*s_fork == SEM_FAILED || *s_death == SEM_FAILED || *s_mutex_death == SEM_FAILED)
		return(printf("Error : Failed to create the semaphore\n"), 1);
	if (sem_close(*s_fork) < 0)
	{
		sem_unlink(S_FORK);
		sem_unlink(S_DEATH);
		sem_unlink(S_MUTEX);
		return(printf("Error : Failed to close the semaphore\n"), 1);
	}
	return (0);
}

int	ft_create_process(t_rules *rules, pid_t *pid)
{
	int	i;
	pid_t pid_child;

	i = 0;
	while (i < rules->number_philo)
	{
		pid_child = fork();
		if (pid_child != 0)
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

void	error(t_rules *mutex, pid_t *pid)
{
	free(pid);
	free_str(mutex->str);
	sem_unlink(S_FORK);	
	sem_unlink(S_DEATH);
	sem_unlink(S_MUTEX);
}
