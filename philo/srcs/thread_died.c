/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_died.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:03:02 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/07 03:30:13 by wdebotte         ###   ########.fr       */
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
			return (-1);
		}
		pthread_mutex_unlock(&infos->philos[i].mutex);
	}
	return (eat);
}

void	check_died_philos(t_infos *infos)
{
	int	eat;

	while (1)
	{
		pthread_mutex_lock(&infos->mutex);
		if ((infos->thr_alive == FALSE || infos->all_eaten == TRUE)
			&& pthread_mutex_unlock(&infos->mutex) == 0)
			return ;
		pthread_mutex_unlock(&infos->mutex);
		eat = check_all_philos(infos);
		if (eat == -1)
			return ;
		usleep(200);
	}
}
