/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:06:14 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 17:21:26 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*check_death(void *arg)
// {
// 	t_rules	*rules;
// 	int		i;

// 	rules = (t_rules *)arg;
// 	pthread_mutex_lock(&rules->mutex_died);
// 	while (rules->is_died != 0)
// 	{
// 		pthread_mutex_unlock(&rules->mutex_died);
// 		usleep(500);
// 		pthread_mutex_lock(&rules->mutex_died);
// 	}
// 	pthread_mutex_unlock(&rules->mutex_died);
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < rules->number_philo)
// 		{
// 			if (rules->time_die <= ft_time(&rules->philo[i]->last_meal,
//				timestamp()))
// 			{
// 				pthread_mutex_lock(&rules->mutex_died);
// 				rules->is_died = 1;
// 				pthread_mutex_unlock(&rules->mutex_died);
// 				pthread_mutex_lock(&rules->mutex_printf);
// 				printf("%ld %d %s\n",ft_time(&rules->time_begin, timestamp()),
//					i + 1, rules->str[e_die]);
// 				pthread_mutex_unlock(&rules->mutex_printf);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 	}
// }