/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:03:47 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/05 11:57:37 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_takes_forks(t_philo *philo)
{
	if (philo->rphilo == NULL)
	{
		print_message(philo, FORK);
		usleep((philo->infos->time_die + 1) * 1000);
		return ;
	}
	pthread_mutex_lock(&philo->infos->mutex);
	if ((philo->infos->thr_alive == FALSE || philo->infos->all_eaten == TRUE)
		&& pthread_mutex_unlock(&philo->infos->mutex) == 0)
		return ;
	pthread_mutex_unlock(&philo->infos->mutex);
	if (philo->id < philo->rphilo->id)
	{
		pthread_mutex_lock(&philo->mutex_fork);
		print_message(philo, FORK);
		pthread_mutex_lock(&philo->rphilo->mutex_fork);
		print_message(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->rphilo->mutex_fork);
		print_message(philo, FORK);
		pthread_mutex_lock(&philo->mutex_fork);
		print_message(philo, FORK);
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->rphilo == NULL)
		return ;
	pthread_mutex_lock(&philo->infos->mutex);
	if ((philo->infos->thr_alive == FALSE
			|| philo->infos->all_eaten == TRUE)
		&& pthread_mutex_unlock(&philo->infos->mutex) == 0)
	{
		pthread_mutex_unlock(&philo->mutex_fork);
		pthread_mutex_unlock(&philo->rphilo->mutex_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	pthread_mutex_lock(&philo->mutex);
	if (philo->n_eat != -1 && philo->n_eat != philo->infos->must_eat)
		philo->n_eat++;
	philo->start_eat = get_time();
	pthread_mutex_unlock(&philo->mutex);
	print_message(philo, EAT);
	_usleep(philo, philo->infos->time_eat);
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&philo->rphilo->mutex_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->rphilo == NULL)
		return ;
	pthread_mutex_lock(&philo->infos->mutex);
	if ((philo->infos->thr_alive == FALSE
			|| philo->infos->all_eaten == TRUE)
		&& pthread_mutex_unlock(&philo->infos->mutex) == 0)
		return ;
	pthread_mutex_unlock(&philo->infos->mutex);
	print_message(philo, SLEEP);
	_usleep(philo, philo->infos->time_sleep);
	print_message(philo, THINK);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex);
	philo->start_eat = get_time();
	pthread_mutex_unlock(&philo->mutex);
	if (philo->infos->n_philos % 2 == 0 && philo->id % 2 == 1)
		usleep(philo->infos->time_eat * 1000);
	else if (philo->infos->n_philos % 2 == 1)
		usleep((philo->infos->time_eat * (philo->id % 3)) * 1000);
	while (philo->infos->thr_alive == TRUE && philo->infos->all_eaten == FALSE)
	{
		philo_takes_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
