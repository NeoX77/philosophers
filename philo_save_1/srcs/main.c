/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:29:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 12:15:36 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_start = get_time();
	philo->last_eat = philo->time_start;
	if (philo->id % 2 == 1)
	{
		if (_usleep(philo->infos, philo->infos->time_eat * 1000) == FALSE)
			return (NULL);
	}
	while (philo->infos->thr_alive == TRUE)
	{
		take_forks(philo);
		philo_eating(philo);
		drop_forks(philo);
		philo_sleeping_and_thinking(philo);
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
