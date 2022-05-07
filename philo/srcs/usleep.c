/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:25:24 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/07 02:09:38 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	_usleep(t_philo *philo, unsigned long time)
{
	unsigned long long	end;

	end = get_time() + time;
	while (get_time() < end)
	{
		pthread_mutex_lock(&philo->infos->mutex);
		if (philo->infos->thr_alive == FALSE || philo->infos->all_eaten == TRUE)
		{
			pthread_mutex_unlock(&philo->infos->mutex);
			return (FALSE);
		}
		pthread_mutex_unlock(&philo->infos->mutex);
		usleep(100);
	}
	return (TRUE);
}
