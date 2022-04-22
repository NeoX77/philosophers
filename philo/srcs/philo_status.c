/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:57:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/22 14:30:46 by wdebotte         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mutex);
	philo->status = EAT;
	print_message(philo, EAT);
	philo->has_eaten++;
	usleep(philo->infos->time_eat * 1000);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_sleeping_and_thinking(t_philo *philo)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	pthread_mutex_lock(&philo->mutex);
	philo->status = SLEEP;
	print_message(philo, SLEEP);
	usleep(philo->infos->time_sleep * 1000);
	pthread_mutex_unlock(&philo->mutex);
	if (philo->infos->thr_alive == FALSE)
		return ;
	pthread_mutex_lock(&philo->mutex);
	philo->status = THINK;
	print_message(philo, THINK);
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
			infos->philos[i].status = DEAD;
			print_message(&infos->philos[i], DEAD);
			infos->thr_alive = FALSE;
			break ;
		}
	}
}
