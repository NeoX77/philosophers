/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_died.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:03:02 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/26 17:04:56 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_philos(t_infos *infos)
{
	int	i;
	int	eat;

	i = -1;
	eat = 0;
	while (++i < infos->n_philos)
	{
		pthread_mutex_lock(&infos->philos[i].mutex);
		if (get_time() - infos->philos[i].start_eat
			> (unsigned long long)infos->time_die)
		{
			pthread_mutex_unlock(&infos->philos[i].mutex);
			print_message(&infos->philos[i], DEAD);
			pthread_mutex_lock(&infos->mutex);
			infos->thr_alive = FALSE;
			pthread_mutex_unlock(&infos->mutex);
			return (-1);
		}
		if (infos->philos[i].n_eat != -1
			&& infos->philos[i].n_eat == infos->must_eat)
			eat++;
		pthread_mutex_unlock(&infos->philos[i].mutex);
	}
	return (eat);
}

void	check_died_philos(t_infos *infos)
{
	int	eat;

	while (infos->thr_alive == TRUE && infos->all_eaten == FALSE)
	{
		eat = check_all_philos(infos);
		if (eat == -1)
			return ;
		else if (eat == infos->n_philos)
		{
			pthread_mutex_lock(&infos->mutex);
			infos->all_eaten = TRUE;
			pthread_mutex_unlock(&infos->mutex);
			return ;
		}
	}
}
