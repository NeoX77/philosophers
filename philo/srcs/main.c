/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:29:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/05 19:10:54 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_infos(t_infos *infos, int args, char **argv)
{
	infos->n_philos = ft_atoi(argv[1]);
	infos->time_die = ft_atoi(argv[2]);
	infos->time_eat = ft_atoi(argv[3]);
	infos->time_sleep = ft_atoi(argv[4]);
	if (args == 6)
		infos->n_can_eat = ft_atoi(argv[5]);
	if (infos->n_philos <= 0)
		return (printf("No one is at the table?\n"));
	if (infos->time_die <= 0)
		return (printf("We all have to die one day right?\n"));
	if (infos->time_eat <= 0)
		return (printf("Can I have more time to eat please?\n"));
	if (infos->time_sleep <= 0)
		return (printf("Let me sleep please!\n"));
	if (infos->n_can_eat == 0)
		infos->n_can_eat = -1;
	return (0);
}

int	main(int args, char **argv)
{
	t_infos	infos;
	//pthread_t	philos[ft_atoi(argv[1])];

	if (args < 5 || args > 6)
	{
		printf("Usage: ./philo \t[number of philosophers]\n\t\t[time to die]\
\n\t\t[time to eat]\n\t\t[time to sleep]\n\t\t[number of how many time \
each philosopher must eat(optionnal)]\nAll time must be in ms!\n");
		return (1);
	}
	if (get_infos(&infos, args, argv) > 0)
		return (2);
}
