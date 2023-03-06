/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:09:40 by jvigny            #+#    #+#             */
/*   Updated: 2023/03/06 19:49:38 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_close_sem(t_semaphore *sem, t_rules *rules, pid_t *pid)
{
	if (sem_close(sem->fork) < 0)
		return (printf("Error : Failed to close the semaphore\n"),
			error(rules, pid, 0), 1);
	if (sem_close(sem->meal) < 0)
		return (printf("Error : Failed to close the semaphore\n"),
			error(rules, pid, 0), 1);
	if (sem_close(sem->mutex) < 0)
		return (printf("Error : Failed to close the semaphore\n"),
			error(rules, pid, 0), 1);
	if (sem_close(sem->death) < 0)
		return (printf("Error : Failed to close the semaphore\n"),
			error(rules, pid, 0), 1);
	error(rules, pid, 0);
	return (0);
}

void	error(t_rules *mutex, pid_t *pid, short boolean)
{
	char			*name_sem;
	char			*name;
	int				i;

	if (boolean == 1)
		free(mutex->str);
	else
		free_str(mutex->str);
	free(pid);
	sem_unlink(S_FORK);
	sem_unlink(S_DEATH);
	sem_unlink(S_MUTEX);
	sem_unlink(S_MEAL);
	i = 1;
	while (i <= mutex->number_philo)
	{
		name = ft_itoa(i);
		name_sem = ft_strjoin("/meal", name);
		if (name_sem != NULL)
			sem_unlink(name_sem);
		free(name_sem);
		free(name);
		++i;
	}
}

void	error_thread(t_philo *philo, char *str)
{
	sem_wait(philo->mutex);
	sem_post(philo->death);
	printf("%s", str);
	sem_close(philo->death);
	sem_close(philo->mutex);
	sem_close(philo->mutex_meal);
	sem_close(philo->meal);
	sem_close(philo->sem);
}

void	kill_process(t_rules *rules, pid_t *pid, pthread_t p_check_meal,
		t_semaphore	*sem)
{
	int	i;

	i = -1;
	while (++i < rules->number_philo)
	{
		if (kill(pid[i], SIGKILL) == -1)
		{
			printf("Error : Failed to kill process\n");
			error(rules, pid, 0);
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while (i < rules->number_philo)
	{
		sem_post(sem->meal);
		++i;
	}
	if (rules->number_eat != -1 && pthread_join(p_check_meal, NULL) != 0)
	{
		printf("Error : Failed to deatch thread\n");
		error(rules, pid, 0);
		exit(EXIT_FAILURE);
	}
	ft_close_sem(sem, rules, pid);
}
