/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:01:01 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/16 19:48:45 by jvigny           ###   ########.fr       */
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

typedef struct s_rules
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
}	t_rules;

enum e_print
{
	e_fork = 0,
	e_eat,
	e_sleep,
	e_think,
	e_die,
};

typedef struct	s_philo
{
	int				nb;
	short			is_died;
	enum e_print	last_action;
	struct timeval	*last_meal;
	int				fork_1;
	int				fork_2;
}	t_philo;

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
int				parsing(int argc, char **argv, t_rules *mutex);

// Action
void			ft_eat(t_rules *rules, t_philo *philo);
void			ft_sleep(t_rules *rules, t_philo *philo);
void			ft_think(t_rules *rules, t_philo *philo);
void			ft_find_fork(t_rules *rules, t_philo *philo);
void			ft_died(t_rules *rules, t_philo *philo);

void			infini_time(t_rules *rules, t_philo *philo);
void			n_time(t_rules *rules, t_philo *philo);
void			action_philo(t_rules *rules, t_philo *philo);
long			ft_time(struct timeval *begin);
void			ft_usleep(long time, t_philo *philo, t_rules *rules);
long			time_conv(struct timeval *time);
long			timestamp(void);
int				ft_init_malloc(t_rules *mutex);
void			ft_init_rules(t_rules *mutex);
void			ft_destroy(t_rules *mutex);
void			ft_create_thread(t_rules *mutex);
void			*philosophers(void	*p);



#endif