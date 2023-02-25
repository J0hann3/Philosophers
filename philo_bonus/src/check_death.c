/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:06:14 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 21:19:07 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_death(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (rules->is_died != 0)
	{
		usleep(500);
	}
	while (1)
	{
		i = 0;
		while (i < rules->number_philo)
		{
			if (rules->time_die <= ft_time(&rules->philo->last_meal,
				timestamp()))
			{
				rules->is_died = 1;
				printf("%ld %d %s\n",ft_time(&rules->time_begin, timestamp()),
					i + 1, rules->str[e_die]);
				return (NULL);
			}
			i++;
		}
	}
}