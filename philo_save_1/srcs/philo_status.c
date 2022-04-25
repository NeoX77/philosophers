/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:57:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 12:16:39 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	pthread_mutex_lock(&philo->mutex_fork);
	print_message(philo, FORK);
	pthread_mutex_lock(&philo->right_philo->mutex_fork);
	print_message(philo, FORK);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&philo->right_philo->mutex_fork);
}

void	philo_eating(t_philo *philo)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	pthread_mutex_lock(&philo->infos->mutex);
	philo->status = EAT;
	print_message(philo, EAT);
	philo->has_eaten++;
	philo->last_eat = get_time();
	if (_usleep(philo->infos, philo->infos->time_eat * 1000) == FALSE)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->infos->mutex);
}

void	philo_sleeping_and_thinking(t_philo *philo)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	pthread_mutex_lock(&philo->infos->mutex);
	philo->status = SLEEP;
	print_message(philo, SLEEP);
	if (_usleep(philo->infos, philo->infos->time_sleep * 1000) == FALSE)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		return ;
	}
	philo->status = THINK;
	print_message(philo, THINK);
	pthread_mutex_unlock(&philo->infos->mutex);
}

void	check_philo_died(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->n_philos)
	{
		if (get_time() - infos->philos[i].last_eat
			> (unsigned long long)infos->time_die)
		{
			printf("%lli, %lli, %i\n", get_time(), infos->philos[i].last_eat, infos->time_die);
			infos->philos[i].status = DEAD;
			print_message(&infos->philos[i], DEAD);
			infos->thr_alive = FALSE;
			break ;
		}
	}
}
