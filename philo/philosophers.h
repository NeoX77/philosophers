/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:16:54 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 14:51:20 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# define FALSE	0
# define TRUE	1

typedef struct s_infos	t_infos;
typedef struct s_philo	t_philo;

struct s_infos
{
	int		n_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		must_eat;
	int		thr_alive;
	t_philo	*philos;
};

struct s_philo
{
	int				id;
	int				n_eat;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	*mutex_rfork;
	t_infos			*infos;
};

//Init
int	set_infos(t_infos *infos, int argc, char **argv);
int	set_philos(t_infos *infos);

// Utils
int	_strlen(char *str);
int	_putstr(char *str);
int	_atoi(char *str);

#endif
