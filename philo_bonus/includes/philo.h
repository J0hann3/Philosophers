/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:01:01 by jvigny            #+#    #+#             */
/*   Updated: 2023/02/27 13:14:52 by jvigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>		/* For O_* constants */
# include <sys/stat.h>	/* For mode constants */
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>


# define S_FORK "/fork"
# define S_DEATH "/death"

enum e_print
{
	e_fork = 0,
	e_eat,
	e_sleep,
	e_think,
	e_die,
};

typedef struct s_philo
{
	int				nb;
	short			is_dead;
	sem_t			*sem;
	enum e_print	last_action;
	struct timeval	last_meal;
}	t_philo;

typedef struct s_rules
{
	struct timeval	time_begin;
	int				time_die;
	int				time_sleep;
	int				time_eat;
	int				time_think;
	int				number_eat;
	int				number_philo;
	char			**str;
}	t_rules;

typedef struct s_thread_death
{
	t_philo		*philo;
	t_rules		*rules;
	pthread_t	thread;
}	t_thread_death;

// typedef struct s_time
// {
// 	time_t		tv_sec;		/* secondes */ long long
// 	suseconds_t	tv_usec;	/* microsecondes */ long long
// }	t_time;

// Utils
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s);
void			free_str(char **res);
size_t			ft_strlen(const char *s);

int				fill_print(char **str);

// Parsing
int				parsing(int argc, char **argv, t_rules *mutex);

// Action
void			ft_eat(t_rules *rules, t_philo *philo);
void			ft_sleep(t_rules *rules, t_philo *philo);
void			ft_think(t_rules *rules, t_philo *philo);
void			ft_find_fork_eat(t_rules *rules, t_philo *philo);
void			ft_died(t_rules *rules, t_philo *philo);

void			infini_time(t_rules *rules, t_philo *philo);
void			n_time(t_rules *rules, t_philo *philo);
void			action_philo(t_rules *rules, t_philo *philo);
long			ft_time(struct timeval *begin, struct timeval now);
void			ft_usleep(struct timeval now, long time, t_philo *philo,
					t_rules *rules);
long			time_conv(struct timeval *time);
struct timeval	timestamp(void);
pid_t			*ft_init_malloc(t_rules *mutex);
int				ft_init_rules(t_rules *mutex);
int				ft_create_thread(t_rules *mutex);
void			philosophers(t_rules *rules, int n_philo);
struct timeval	ft_printf(t_rules *rules, t_philo *philo, enum e_print etat);
void			error(t_rules *mutex, pid_t *pid);
void			*check_death(void *arg);

#endif