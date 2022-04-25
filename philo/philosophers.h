/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:16:54 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 16:28:09 by wdebotte         ###   ########.fr       */
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

typedef struct s_infos	t_infos;
typedef struct s_philo	t_philo;

struct s_infos
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				thr_alive;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_message;
	t_philo			*philos;
};

struct s_philo
{
	int					id;
	int					n_eat;
	unsigned long long	time_start;
	pthread_mutex_t		mutex_fork;
	pthread_mutex_t		*mutex_rfork;
	pthread_t			thread;
	t_infos				*infos;
};

//Routine
void				*routine(void *arg);

//Init
int					set_infos(t_infos *infos, int argc, char **argv);
int					set_philos(t_infos *infos);
int					set_threads(t_infos *infos);

//Utils
int					_strlen(char *str);
int					_putstr(char *str);
int					_atoi(char *str);
int					exit_program(t_infos *infos);
unsigned long long	get_ms_time(void);

#endif
