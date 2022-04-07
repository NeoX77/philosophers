/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:36:27 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/07 15:59:27 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

# define START	0
# define EAT	1
# define THINK	2
# define SLEEP	3

typedef struct s_philo	t_philo;
typedef struct s_infos	t_infos;

struct s_philo
{
	int				id;
	int				status;
	int				has_fork;
	int				has_eaten;
	pthread_mutex_t	mutex_fork;
	t_philo			*next;
};

struct s_infos
{
	int	philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	max_eat;
	int	time_day;
};

int	ft_atoi(char *str);

#endif
