/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:57:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/08 16:18:27 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

typedef struct s_sideforks	t_sideforks;

struct s_sideforks
{
	t_philo	*philo_right;
	t_philo	*philo_left;
};

void	set_side_philos(t_philo *philo, t_sideforks *forks)
{
	t_infos	*infos;

	infos = philo->infos;
	if (philo->id == 1)
	{
		forks->philo_right = &infos->philos[philo->id + 1];
		forks->philo_left = &infos->philos[infos->n_philos - 1];
	}
	else if (philo->id == infos->n_philos)
	{
		forks->philo_right = &infos->philos[0];
		forks->philo_left = &infos->philos[philo->id - 1];
	}
	else
	{
		forks->philo_right = &infos->philos[philo->id + 1];
		forks->philo_left = &infos->philos[philo->id - 1];
	}
}

int	can_eat(t_philo *philo, t_sideforks *forks)
{
	t_infos	*infos;

	infos = philo->infos;
	if (infos->n_philos < 2)
		return (FALSE);
	set_side_philos(philo, forks);
	pthread_mutex_lock(&forks->philo_right->mutex_fork);
	pthread_mutex_lock(&forks->philo_left->mutex_fork);
	if (forks->philo_right->has_fork == TRUE
			&& forks->philo_left->has_fork == TRUE)
		return (TRUE);
	else
	{
		pthread_mutex_unlock(&forks->philo_right->mutex_fork);
		pthread_mutex_unlock(&forks->philo_left->mutex_fork);
	}
	return (FALSE);
}

int	philo_eating(t_philo *philo)
{
	t_sideforks	forks;

	if (can_eat(philo, &forks) == TRUE)
	{
		printf("Philosopher [%i] has taken a fork\n", philo->id);
		forks.philo_right->has_fork = FALSE;
		forks.philo_left->has_fork = FALSE;
		philo->status = EAT;
		philo->has_eaten++;
		usleep(philo->infos->time_eat);
		forks.philo_right->has_fork = TRUE;
		forks.philo_left->has_fork = TRUE;
		pthread_mutex_unlock(&forks.philo_right->mutex_fork);
		pthread_mutex_unlock(&forks.philo_left->mutex_fork);
		return (TRUE);
	}
	else
		return (FALSE);
}
