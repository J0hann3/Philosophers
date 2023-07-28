/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:04:29 by jvigny            #+#    #+#             */
/*   Updated: 2023/07/28 15:09:52 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


int	parsing(int argc, char **argv, t_rules *mutex)
{
	if (argc < 5 || argc > 6)
		return (-1);
	mutex->number_philo = ft_atoi(argv[1]);
	if (mutex->number_philo == -1)
		return (-1);
	mutex->time_die = ft_atoi(argv[2]);
	if (mutex->time_die == -1)
		return (-1);
	mutex->time_eat = ft_atoi(argv[3]);
	if (mutex->time_eat == -1)
		return (-1);
	mutex->time_sleep = ft_atoi(argv[4]);
	if (mutex->time_sleep == -1)
		return (-1);
	if (argc == 6)
	{
		mutex->number_eat = ft_atoi(argv[5]);
		if (mutex->number_eat == -1)
			return (-1);
	}
	else
		mutex->number_eat = -1;
	return (1);
}
