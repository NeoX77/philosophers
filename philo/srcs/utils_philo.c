/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:34:50 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/22 14:35:07 by wdebotte         ###   ########.fr       */
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
    :q
		if (pthread_mutex_destroy(&infos->philos[i].mutex) != 0
			|| pthread_mutex_destroy(&infos->philos[i].mutex_fork) != 0)
			printf("Error mutex [id:%i]: Can't destroy mutex.\n",
				infos->philos[i].id);
		i++;
	}
}
