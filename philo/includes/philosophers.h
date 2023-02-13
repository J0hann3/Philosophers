/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:01:01 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/13 20:21:51 by jvigny           ###   ########.fr       */
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
	int				index;
	char			**str;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_index;
	pthread_mutex_t	mutex_printf;
	pthread_t		*philo;			// Not sure it's usefull in the struct
}	t_mutex;

enum e_print
{
	e_fork = 0,
	e_eat,
	e_sleep,
	e_think,
	e_die,
};

// typedef struct s_time
// {
// 	time_t		tv_sec;		/* secondes */
// 	suseconds_t	tv_usec;	/* microsecondes */
// }	t_time;

// Utils
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
void	free_str(char **res);
size_t	ft_strlen(const char *s);

void	fill_print(char **str);

// Parsing
int		parsing(int argc, char **argv, t_mutex *mutex);

void	infini_time(t_mutex *philo, int nb, struct timeval *begin);
void	action_philo(t_mutex *philo, int nb, struct timeval *begin);
void	n_time(t_mutex *philo, int nb, struct timeval *begin);
int		ft_time(struct timeval *begin);

#endif