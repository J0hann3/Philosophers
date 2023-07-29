/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:00:48 by jvigny            #+#    #+#             */
/*   Updated: 2023/07/29 16:34:12 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

#if DEBUG
FILE *fd;
#endif

int	philosophers(t_rules *rules, int n_philo)
{
	t_philo			philo;
	t_thread_death	death;

	philo.nb = n_philo + 1;
	ft_open_sem(&philo);
	philo.last_meal.tv_sec = rules->time_begin.tv_sec;
	philo.last_meal.tv_usec = rules->time_begin.tv_usec;
	if (rules->number_philo % 2 == 0)
		philo.last_action = philo.nb % 2;
	else
		philo.last_action = philo.nb % 3;
	death.philo = &philo;
	death.rules = rules;
	if (pthread_create(&death.thread, NULL, &check_death, (void *)&death) != 0)
		return (error_thread(&philo, "Error : Failed to create thread\n"), 1);
	if (pthread_detach(death.thread) != 0)
		return (error_thread(&philo, "Error : Failed to detach thread\n"), 1);
	if (rules->number_eat == -1)
		infini_time(rules, &philo);
	else
		n_time(rules, &philo);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t		*pid;
	pthread_t	p_check_meal;
	t_rules		rules;
	t_semaphore	sem;

#if DEBUG
	fd = fopen("test.txt", "wr");
#endif
	if (parsing(argc, argv, &rules) == -1)
		return (printf("Error : Incorrect arguments\n"), 1);
	if (rules.number_philo == 0 || rules.number_eat == 0)
		return (0);
	rules.time_think = (rules.number_philo % 2) * rules.time_eat;
	pid = ft_init_malloc(&rules);
	if (pid == NULL)
		return (printf("Error : Failed to allocated memory\n"), 1);
	gettimeofday(&rules.time_begin, NULL);
	ft_init_semaphore(&rules, &sem, pid);
	sem.nb_philo = rules.number_philo;
	if (rules.number_eat != -1 && pthread_create(&p_check_meal, NULL,
			&check_meal, (void *)&sem) != 0)
		return (printf("Error : Failed to create thread\n"),
			error(&rules, pid, 0), 1);
	if (ft_create_process(&rules, pid) <= 0)
		return (0);
	sem_wait(sem.death);
	kill_process(&rules, pid, p_check_meal, &sem);
#if DEBUG
	fclose(fd);
#endif
	return (0);
}
