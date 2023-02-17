/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:14:33 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/17 19:07:10 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_print(char **str)
{
	str[0] = ft_strdup("has taken a fork");
	str[1] = ft_strdup("is eating");
	str[2] = ft_strdup("is sleeping");
	str[3] = ft_strdup("is thinking");
	str[4] = ft_strdup("died");
}

void	ft_printf(t_rules *rules, t_philo *philo, enum e_print etat)
{
	pthread_mutex_lock(&rules->mutex_died);
	if (rules->is_died != 1)
	{
		pthread_mutex_unlock(&rules->mutex_died);
		pthread_mutex_lock(&rules->mutex_printf);
		printf("%ld %d %s\n",ft_time(&rules->time_begin), philo->nb, rules->str[etat]);
		pthread_mutex_unlock(&rules->mutex_printf);
	}
	else
		pthread_mutex_unlock(&rules->mutex_died);
}
