/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:13:31 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 17:11:03 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_time(struct timeval *begin)
{
	struct timeval time;
	int				milli;

	gettimeofday(&time, NULL);
	// printf("time : %ld\n", (time).tv_usec / 1000 + (time).tv_sec * 1000);
	milli = (time.tv_usec - begin->tv_usec) / 1000 + (time.tv_sec - begin->tv_sec) * 1000;
	return (milli);
}

long	timestamp(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

long	time_conv(struct timeval *time)
{
	return (time->tv_usec / 1000 + time->tv_sec * 1000);
}