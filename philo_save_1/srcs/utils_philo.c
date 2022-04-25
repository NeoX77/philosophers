/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:34:50 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 11:59:45 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	destroy_mutexes(t_infos *infos)
{
	int	i;

	if (pthread_mutex_destroy(&infos->mutex_message) != 0)
		printf("Error mutex: Can't destroy mutex.\n");
	i = 0;
	while (i < infos->n_philos)
	{
		if (pthread_mutex_destroy(&infos->mutex) != 0
			|| pthread_mutex_destroy(&infos->philos[i].mutex_fork) != 0)
			printf("Error mutex [id:%i]: Can't destroy mutex.\n",
				infos->philos[i].id);
		i++;
	}
}

int	_usleep(t_infos *infos, useconds_t usec)
{
	while (usec > 0)
	{
		if (infos->thr_alive == FALSE)
			return (FALSE);
		if (usec > 100)
		{
			usleep(100);
			usec -= 100;
		}
		else if (usec > 25)
		{
			usleep(10);
			usec -= 10;
		}
		else if (usec > 0)
		{
			usleep(1);
			usec -= 1;
		}
	}
	return (TRUE);
}
