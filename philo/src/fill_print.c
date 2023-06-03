/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:14:33 by jvigny            #+#    #+#             */
/*   Updated: 2023/06/03 18:52:19 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fill_print(char **str)
{
	str[0] = ft_strdup("has taken a fork");
	str[1] = ft_strdup("is eating");
	str[2] = ft_strdup("is sleeping");
	str[3] = ft_strdup("is thinking");
	str[4] = ft_strdup("died");
	if (str[0] == NULL || str[1] == NULL || str[2] == NULL || str[3] == NULL
		|| str[4] == NULL)
	{
		free_str(str);
		return (1);
	}
	return (0);
}

struct timeval	ft_printf(t_rules *rules, t_philo *philo, enum e_print etat)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&rules->mutex_died);
	if (rules->is_died != 1)
	{
		pthread_mutex_lock(&rules->mutex_printf);
		printf("%ld %d %s\n", ft_time(&rules->time_begin, time), philo->nb,
			rules->str[etat]);
		pthread_mutex_unlock(&rules->mutex_printf);
	}
	pthread_mutex_unlock(&rules->mutex_died);
	return (time);
}

void	ft_died(t_rules *rules, t_philo *philo)
{
	rules->is_died = 1;
	pthread_mutex_lock(&rules->mutex_printf);
	printf("%ld %d %s\n", ft_time(&rules->time_begin, timestamp()), philo->nb,
		rules->str[e_die]);
	pthread_mutex_unlock(&rules->mutex_printf);
}
