/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:41:30 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/22 14:11:54 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_infos(t_infos *infos, int argc, char **argv)
{
	infos->n_philos = ft_atoi(argv[1]);
	if (infos->n_philos < 1)
		return (ft_putstr("Args error: Minimum one philosopher is needed.\n"));
	infos->time_die = ft_atoi(argv[2]);
	infos->time_eat = ft_atoi(argv[3]);
	infos->time_sleep = ft_atoi(argv[4]);
	if (infos->time_die <= 0 || infos->time_eat <= 0 || infos->time_sleep <= 0)
		return (ft_putstr("Args error: All time must be > than 0.\n"));
	if (argc == 6)
		infos->max_eat = ft_atoi(argv[5]);
	infos->thr_alive = TRUE;
	if (pthread_mutex_init(&infos->mutex_message, NULL) != 0)
		return (ft_putstr("Mutex error: Can't init mutex.\n"));
	return (0);
}

int	init_forks(t_infos *infos)
{
	int		i;
	int		id;
	t_philo	*philo;

	i = 0;
	while (i < infos->n_philos)
	{
		philo = &infos->philos[i];
		id = philo->id - 1;
		if (infos->n_philos == 1)
			infos->philos[i].right_philo = NULL;
		else if (philo->id + 1 > infos->n_philos)
			infos->philos[i].right_philo = &infos->philos[0];
		else
			infos->philos[i].right_philo = &infos->philos[id + 1];
		i++;
	}
	return (0);
}

int	init_philos(t_infos *infos)
{
	int	i;

	infos->philos = malloc(sizeof(t_philo) * infos->n_philos);
	if (infos->philos == NULL)
		return (1);
	i = 0;
	while (i < infos->n_philos)
	{
		infos->philos[i].id = i + 1;
		infos->philos[i].status = THINK;
		infos->philos[i].has_eaten = 0;
		infos->philos[i].time_start = 0;
		infos->philos[i].last_eat = 0;
		if (pthread_mutex_init(&infos->philos[i].mutex, NULL) != 0
			|| pthread_mutex_init(&infos->philos[i].mutex_fork, NULL) != 0)
			return (ft_putstr("Mutex error: Can't init mutex(es)."));
		infos->philos[i].infos = infos;
		i++;
	}
	return (init_forks(infos));
}

int	init_threads(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->n_philos)
	{
		if (pthread_create(&infos->philos[i].thread, NULL, &routine,
				&infos->philos[i]) != 0)
			return (ft_putstr("Thread error: Can't create thread.\n"));
		i++;
	}
	while (infos->thr_alive == TRUE)
		check_philo_died(infos);
	i = 0;
	while (i < infos->n_philos)
	{
		if (pthread_join(infos->philos[i].thread, NULL) != 0)
			return (ft_putstr("Thread error: Can't join thread.\n"));
		i++;
	}
	return (0);
}
