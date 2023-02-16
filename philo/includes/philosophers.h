/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:01:01 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 18:08:26 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_mutex
{
	struct timeval	*time_begin;
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
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s);
void			free_str(char **res);
size_t			ft_strlen(const char *s);

void			fill_print(char **str);

// Parsing
int				parsing(int argc, char **argv, t_mutex *mutex);

// Action
void			ft_eat(t_mutex *philo, int nb, struct timeval *last);
void			ft_sleep(t_mutex *philo, int nb, struct timeval *last);
void			ft_think(t_mutex *philo, int nb);
void			ft_find_fork(t_mutex *philo, int nb, struct timeval *last);

void			infini_time(t_mutex *philo, int nb);
void			n_time(t_mutex *philo, int nb);
void			action_philo(t_mutex *philo, int nb, struct timeval *begin);
int				ft_time(struct timeval *begin);
void			ft_usleep(long time, long last_meal, t_mutex *philo);
long			time_conv(struct timeval *time);
long			timestamp(void);
int				ft_init_malloc(t_mutex *mutex);
void			ft_init_mutex(t_mutex *mutex);
void			ft_destroy(t_mutex *mutex);
void			ft_create_thread(t_mutex *mutex);
void			*philosophers(void	*p);



#endif