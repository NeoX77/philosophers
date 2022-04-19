/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:36:27 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/19 23:23:29 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define THINK	1
# define EAT	2
# define SLEEP	3

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
	unsigned long long	start_eat;
	unsigned long long	last_eat;
	t_philo				*right_philo;
	pthread_t			thread;
	pthread_mutex_t		mutex;
	pthread_mutex_t		mutex_fork;
	t_infos				*infos;
};

struct s_infos
{
	int		n_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		max_eat;
	int		thr_alive;
	t_philo	*philos;
};

int					ft_strlen(char *str);
int					ft_putstr(char *str);
int					ft_atoi(char *str);
int					get_infos(t_infos *infos, int argc, char **argv);
int					init_philos(t_infos *infos);
int					init_threads(t_infos *infos);
int					philo_eating(t_philo *philo);

void				*routine(void *arg);
void				destroy_mutexes(t_infos *infos);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);

unsigned long long	get_time(void);

#endif
