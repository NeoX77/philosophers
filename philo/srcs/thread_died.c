/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_died.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:03:02 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/07 05:48:33 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_philos(t_infos *infos)
{
	int	i;

	i = -1;
	while (++i < infos->n_philos)
	{
		pthread_mutex_lock(&infos->philos[i].mutex);
		if (get_time() - infos->philos[i].start_eat
			> (unsigned long long)infos->time_die)
		{
			pthread_mutex_unlock(&infos->philos[i].mutex);
			print_message(&infos->philos[i], DEAD);
			return (FALSE);
		}
		pthread_mutex_unlock(&infos->philos[i].mutex);
	}
	return (TRUE);
}

void	check_died_philos(t_infos *infos)
{
	while (1)
	{
		pthread_mutex_lock(&infos->mutex);
		if ((infos->thr_alive == FALSE || infos->all_eaten == TRUE)
			&& pthread_mutex_unlock(&infos->mutex) == 0)
			return ;
		pthread_mutex_unlock(&infos->mutex);
		if (check_all_philos(infos) == FALSE)
			return ;
		usleep(200);
	}
}
