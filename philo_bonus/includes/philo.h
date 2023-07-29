/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigny <jvigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:01:01 by jvigny            #+#    #+#             */
/*   Updated: 2023/07/29 17:26:35 by jvigny           ###   ########.fr       */
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
# include <stdbool.h>

# define S_FORK "/fork"
# define S_DEATH "/death"
# define S_MUTEX "/mutex"
# define S_MEAL "/meal"

enum e_print
{
	e_sleep = 0,
	e_eat,
	e_think,
	e_fork,
	e_die,
};

typedef struct s_pinthilo
{
	int				nb;
	sem_t			*sem;
	sem_t			*mutex_meal;
	sem_t			*mutex;
	sem_t			*death;
	sem_t			*meal;
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

typedef struct s_semaphore
{
	int				nb_philo;
	sem_t			*meal;
	sem_t			*death;
	sem_t			*mutex;
	sem_t			*fork;
}	t_semaphore;

// Utils
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s);
void			free_str(char **res);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);

// Parsing
int				parsing(int argc, char **argv, t_rules *mutex);

//----- Init ------
pid_t			*ft_init_malloc(t_rules *mutex);
void			ft_init_semaphore(t_rules *rules, t_semaphore *sem, pid_t *pid);
int				ft_create_process(t_rules *rules, pid_t *pid);
void			ft_open_sem(t_philo *philo);
int				philosophers(t_rules *rules, int n_philo);

// Action
void			ft_eat(t_rules *rules, t_philo *philo);
void			ft_sleep(t_rules *rules, t_philo *philo);
void			ft_think(t_rules *rules, t_philo *philo);
void			ft_find_fork_eat(t_rules *rules, t_philo *philo);

int				fill_print(char **str);
struct timeval	ft_printf(t_rules *rules, t_philo *philo, enum e_print etat);
void			infini_time(t_rules *rules, t_philo *philo);
void			n_time(t_rules *rules, t_philo *philo);

// -------- Time -------
long			ft_time(struct timeval *begin, struct timeval now);
long			time_conv(struct timeval *time);
struct timeval	timestamp(void);

// ------ Thread ------
void			*check_death(void *arg);
void			*check_meal(void *arg);

// ------- Clear ------
void			kill_process(t_rules *rules, pid_t *pid, pthread_t p_check_meal,
					t_semaphore	*sem);
int				ft_close_sem(t_semaphore *sem, t_rules *rules, pid_t *pid);
void			error(t_rules *mutex, pid_t *pid, short boolean);
void			error_thread(t_philo *philo, char *str);

#endif