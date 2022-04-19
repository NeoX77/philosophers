/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:34:04 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/19 14:01:34 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_putstr(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	ft_atoi(char *str)
{
	int			i;
	int			is_negativ;
	long int	nbr;

	nbr = 0;
	is_negativ = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		if (str[i++] == '-')
			is_negativ = -is_negativ;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		nbr = nbr * 10 + str[i++] - '0';
	return (nbr * is_negativ);
}

unsigned long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	destroy_mutexes(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->n_philos)
	{
		pthread_mutex_destroy(&infos->philos[i].mutex_fork);
		i++;
	}
}
