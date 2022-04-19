/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:57:21 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/19 18:36:13 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo, int drop)
{
	if (drop == FALSE)
	{
		//pthread_mutex_lock(&philo->mutex_fork);
		//pthread_mutex_lock(&philo->right_philo->mutex_fork);
		philo->has_fork = FALSE;
		philo->right_philo->has_fork = FALSE;
		printf("%lli %i has taken a fork\n", get_time() - philo->time_start,
			philo->id);
		printf("%lli %i has taken a fork\n", get_time() - philo->time_start,
			philo->id);
	}
	else
	{
		philo->has_fork = TRUE;
		philo->right_philo->has_fork = TRUE;
		//pthread_mutex_unlock(&philo->mutex_fork);
		//pthread_mutex_unlock(&philo->right_philo->mutex_fork);
	}
}

int	philo_eating(t_philo *philo)
{
	if (philo->has_fork == TRUE && philo->right_philo->has_fork == TRUE)
	{
		take_forks(philo, FALSE);
		philo->status = EAT;
		//philo->has_eaten++;
		usleep(philo->infos->time_eat * 1000);
		take_forks(philo, TRUE);
		return (TRUE);
	}
	else
	{
		if (get_time() - philo->start_eat
			> (unsigned long long)philo->infos->time_die)
		{
			printf("%lli %i died\n", get_time() - philo->time_start, philo->id);
			philo->infos->thr_alive = FALSE;
		}
		else
			return (philo_eating(philo));
		return (FALSE);
	}
}
