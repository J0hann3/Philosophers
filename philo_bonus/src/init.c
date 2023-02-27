/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:40:52 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 13:15:14 by jvigny           ###   ########.fr       */
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

void	error(t_rules *mutex, pid_t *pid)
{
	free(pid);
	free_str(mutex->str);
}
