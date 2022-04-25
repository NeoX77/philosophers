/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:39:54 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 16:57:16 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	set_infos(t_infos *infos, int argc, char **argv)
{
	infos->n_philos = _atoi(argv[1]);
	if (infos->n_philos < 1)
		return (_putstr("Args error: Minimum 1 philosopher is needed.\n"));
	infos->time_die = _atoi(argv[2]);
	infos->time_eat = _atoi(argv[3]);
	infos->time_sleep = _atoi(argv[4]);
	if (infos->time_die <= 0 || infos->time_eat <= 0 || infos->time_sleep <= 0)
		return (_putstr("Args error: All times must be > than 0 and only \
composed by digits.\n"));
	if (argc == 6)
	{
		infos->must_eat = _atoi(argv[5]);
		if (infos->must_eat <= 0)
			return (_putstr("Args error: must_eat must be > than 0 and only \
composed by digits.\n"));
	}
	infos->thr_alive = TRUE;
	if (pthread_mutex_init(&infos->mutex, NULL) != 0
		|| pthread_mutex_init(&infos->mutex_message, NULL) != 0)
		return (_putstr("Mutex error: Can't init mutex.\n"));
	return (0);
}

int	set_forks(t_infos *infos)
{
	int	i;

	i = -1;
	while (++i < infos->n_philos)
	{
		if (pthread_mutex_init(&infos->philos[i].mutex_fork, NULL) != 0)
			return (_putstr("Mutex error: Can't init mutex.\n"));
		if (i == 0)
			continue ;
		else if (i + 1 == infos->n_philos)
			infos->philos[i].mutex_rfork = &infos->philos[0].mutex_fork;
		else
			infos->philos[i - 1].mutex_rfork = &infos->philos[i].mutex_fork;
	}
	return (0);
}

int	set_philos(t_infos *infos)
{
	int	i;

	infos->philos = malloc(sizeof(t_philo) * infos->n_philos);
	if (infos->philos == NULL)
		return (_putstr("Malloc error: Can't malloc philo's tab.\n"));
	i = -1;
	while (++i < infos->n_philos)
	{
		infos->philos[i].id = i + 1;
		infos->philos[i].n_eat = 0;
		infos->philos[i].infos = infos;
	}
	return (set_forks(infos));
}

int	set_threads(t_infos *infos)
{
	int	i;

	i = -1;
	while (++i < infos->n_philos)
		if (pthread_create(&infos->philos[i].thread, NULL, &routine,
				&infos->philos[i]) != 0)
			return (_putstr("Thread error: Can't create thread.\n"));
//	check_died_philos(infos);
	i = -1;
	while (++i < infos->n_philos)
		if (pthread_join(infos->philos[i].thread, NULL) != 0)
			return (_putstr("Thread error: Can't join thread.\n"));
	return (0);
}
