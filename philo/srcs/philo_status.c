/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:57:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/19 23:24:50 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	printf("%lli %i has taken a fork\n", get_time() - philo->time_start,
		philo->id);
	pthread_mutex_lock(&philo->right_philo->mutex_fork);
	printf("%lli %i has taken a fork\n", get_time() - philo->time_start,
		philo->id);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&philo->right_philo->mutex_fork);
}

int	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = get_time();
	if (philo->last_eat - philo->start_eat
		> (unsigned long long)philo->infos->time_die)
	{
		philo->infos->thr_alive = FALSE;
		printf("%lli %i died\n", get_time() - philo->time_start, philo->id);
		return (FALSE);
	}
	philo->status = EAT;
	usleep(philo->infos->time_eat * 1000);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->mutex);
	return (TRUE);
}
