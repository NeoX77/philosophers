/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:29:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/19 18:34:17 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->time_start == 0)
		philo->time_start = get_time();
	while (philo->infos->thr_alive == TRUE)
	{
		if (philo->status == THINK)
		{
			philo->start_eat = get_time();
			if (philo_eating(philo) == FALSE)
				break ;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_infos	infos;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo \t[number of philosophers]\n\t\t[time to die]\
\n\t\t[time to eat]\n\t\t[time to sleep]\n\t\t[number of how many time \
each philosopher must eat(optionnal)]\nAll time must be in ms!\n");
		return (1);
	}
	if (get_infos(&infos, argc, argv) > 0)
		return (1);
	if (init_philos(&infos) > 0)
		return (1);
	if (init_threads(&infos) > 0)
		return (1);
	destroy_mutexes(&infos);
	free(infos.philos);
	return (0);
}
