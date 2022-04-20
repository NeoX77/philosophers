/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:57:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/20 17:51:57 by wdebotte         ###   ########.fr       */
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

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->status = EAT;
	printf("%lli %i is eating\n", get_time() - philo->time_start, philo->id);
	philo->has_eaten++;
	usleep(philo->infos->time_eat * 1000);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_sleeping_and_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->status = SLEEP;
	printf("%lli %i is sleeping\n", get_time() - philo->time_start, philo->id);
	usleep(philo->infos->time_sleep * 1000);
	philo->status = THINK;
	printf("%lli %i is thinking\n", get_time() - philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->mutex);
}

void	check_philo_died(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->n_philos)
	{
		if (get_time() - infos->philos[i].last_eat
			<= (unsigned long long)infos->time_die * 1000)
		{
			printf("%lli %i died\n", get_time() - infos->philos[i].time_start,
				infos->philos[i].id);
			infos->philos[i].status = DEAD;
			infos->thr_alive = FALSE;
			break ;
		}
	}
}
