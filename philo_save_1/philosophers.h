/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:36:27 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 11:59:12 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK	0
# define EAT	1
# define SLEEP	2
# define THINK	3
# define DEAD	4

# define FALSE	0
# define TRUE	1

typedef struct s_philo	t_philo;
typedef struct s_infos	t_infos;

struct s_philo
{
	int					id;
	int					status;
	int					has_eaten;
	unsigned long long	time_start;
	unsigned long long	last_eat;
	t_philo				*right_philo;
	pthread_t			thread;
	pthread_mutex_t		mutex_fork;
	t_infos				*infos;
};

struct s_infos
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_eat;
	int				thr_alive;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_message;
	t_philo			*philos;
};

int					ft_strlen(char *str);
int					ft_putstr(char *str);
int					ft_atoi(char *str);
int					get_infos(t_infos *infos, int argc, char **argv);
int					init_philos(t_infos *infos);
int					init_threads(t_infos *infos);
int					_usleep(t_infos *infos, useconds_t usec);

void				*routine(void *arg);
void				destroy_mutexes(t_infos *infos);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
void				philo_eating(t_philo *philo);
void				philo_sleeping_and_thinking(t_philo *philo);
void				check_philo_died(t_infos *infos);
void				print_message(t_philo *philo, int type);

unsigned long long	get_time(void);

#endif
