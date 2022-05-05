/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:25:24 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/05 14:16:08 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	_usleep(t_philo *philo, unsigned long time)
{
	unsigned long long	end;

	(void)philo;
	pthread_mutex_lock(&philo->mutex);
	end = get_time() + time;
	while (get_time() < end)
	{
		if (philo->infos->thr_alive == FALSE || philo->infos->all_eaten == TRUE)
		{
			pthread_mutex_unlock(&philo->mutex);
			return (FALSE);
		}
		usleep(100);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (TRUE);
}
