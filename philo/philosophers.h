/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:01:01 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/11 19:49:45 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_mutex
{
	int				time_die;
	int				time_sleep;
	int				time_eat;
	int				number_eat;
	int				number_philo;
	char			*str;
	pthread_t		*philo;			// Not sure it's usefull in the struct
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_printf;
}	t_mutex;

typedef struct s_time
{
	time_t		tv_sec;		/* secondes */
	suseconds_t	tv_usec;	/* microsecondes */
}	t_time;

// Utils
int	ft_atoi(const char *str);

// Parsing
int	parsing(int argc, char **argv, t_mutex *mutex);

#endif