/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:03:47 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 17:46:55 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forks_status(t_philo *philo, int has_fork)
{
	if (has_fork == FALSE)
	{
		pthread_mutex_lock(&philo->mutex_fork);
		print_message(philo, FORK);
		pthread_mutex_lock(&philo->rphilo->mutex_fork);
		print_message(philo, FORK);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex_fork);
		pthread_mutex_unlock(&philo->rphilo->mutex_fork);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_start = get_time();
	if (philo->id % 2 == 1)
		usleep(philo->infos->time_eat * 1000);
	while (philo->infos->thr_alive == TRUE)
	{
		forks_status(philo, FALSE);
		forks_status(philo, TRUE);
	}
	return (NULL);
}
