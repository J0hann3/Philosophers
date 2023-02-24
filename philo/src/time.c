/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:13:31 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/24 12:26:55 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_time(struct timeval *begin, struct timeval now)
{
	long	milli;

	milli = time_conv(&now) - time_conv(begin);
	return (milli);
}

struct timeval	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

long	time_conv(struct timeval *time)
{
	if (time == NULL)
		return (0);
	return (time->tv_usec / 1000 + time->tv_sec * 1000);
}
