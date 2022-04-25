/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:05:29 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/22 14:13:41 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, int type)
{
	if (philo->infos->thr_alive == FALSE)
		return ;
	pthread_mutex_lock(&philo->infos->mutex_message);
	printf("%lli %i", get_time() - philo->time_start, philo->id);
	if (type == FORK)
		printf(" has taken a fork\n");
	else if (type == EAT)
		printf(" is eating\n");
	else if (type == SLEEP)
		printf(" is sleeping\n");
	else if (type == THINK)
		printf(" is thinking\n");
	else
		printf(" died\n");
	pthread_mutex_unlock(&philo->infos->mutex_message);
}
