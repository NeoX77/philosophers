/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:28:40 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 16:20:20 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	_putstr(char *str)
{
	return (write(1, str, _strlen(str)));
}

int	_atoi(char *str)
{
	long int	nbr;

	nbr = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
		return (-1);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (-1);
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	return (nbr);
}

int	exit_program(t_infos *infos)
{
	int	i;

	i = -1;
	while (++i < infos->n_philos)
	{
		if (pthread_mutex_destroy(&infos->philos[i].mutex_fork) != 0)
			printf("Mutex error: An error occured destroying mutex [%i].\n",
				infos->philos[i].id);
	}
	if (pthread_mutex_destroy(&infos->mutex) != 0
		|| pthread_mutex_destroy(&infos->mutex_message) != 0)
		_putstr("Mutex error: Can't destroy infos mutexes.\n");
	free(infos->philos);
	return (0);
}

unsigned long long	get_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
