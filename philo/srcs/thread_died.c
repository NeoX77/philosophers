/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_died.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:03:02 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/26 13:23:39 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_died_philos(t_infos *infos)
{
	int	i;

	while (infos->thr_alive == TRUE)
	{
		i = -1;
		while (++i < infos->n_philos)
		{
			if (get_time() - infos->philos[i].start_eat
				> (unsigned long long)infos->time_die)
			{
				print_message(&infos->philos[i], DEAD);
				infos->thr_alive = FALSE;
				break ;
			}
		}
	}
}
