/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:03:47 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/26 13:54:19 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forks_status(t_philo *philo, int has_fork)
{
	if (philo->infos->thr_alive == FALSE)
	{
		if (has_fork == TRUE)
		{
			pthread_mutex_unlock(&philo->mutex_fork);
			pthread_mutex_unlock(&philo->rphilo->mutex_fork);
		}
		return ;
	}
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

void	philo_eat(t_philo *philo)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	if (philo->n_eat != -1 && philo->n_eat != philo->infos->must_eat)
		philo->n_eat++;
	print_message(philo, EAT);
	philo->start_eat = get_time();
	usleep(philo->infos->time_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	print_message(philo, SLEEP);
	usleep(philo->infos->time_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	print_message(philo, THINK);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_eat = get_time();
	philo->time_start = get_time();
	if (philo->id % 3 > 1)
		usleep(philo->infos->time_eat * 1000);
	while (philo->infos->thr_alive == TRUE)
	{
		forks_status(philo, FALSE);
		philo_eat(philo);
		forks_status(philo, TRUE);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
