/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:27:30 by wdebotte          #+#    #+#             */
/*   Updated: 2022/05/07 05:39:58 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define RED		"\033[91m"
#define GREEN	"\033[92m"
#define YELLOW	"\033[93m"
#define PURPLE	"\033[95m"
#define CYAN	"\033[96m"
#define END		"\033[0m"

char	*set_color(int type)
{
	if (type == FORK)
		return (PURPLE);
	else if (type == EAT)
		return (GREEN);
	else if (type == SLEEP)
		return (YELLOW);
	else if (type == THINK)
		return (CYAN);
	else
		return (RED);
}

void	print_eating(t_philo *philo)
{
	int	i;
	int	eat;

	eat = 0;
	i = -1;
	while (++i < philo->infos->n_philos)
	{
		pthread_mutex_lock(&philo->infos->philos[i].mutex);
		if (philo->infos->philos[i].n_eat != -1
			&& philo->infos->philos[i].n_eat == philo->infos->must_eat)
			eat++;
		pthread_mutex_unlock(&philo->infos->philos[i].mutex);
	}
	if (eat == philo->infos->n_philos)
	{
		pthread_mutex_lock(&philo->infos->mutex);
		philo->infos->all_eaten = TRUE;
		pthread_mutex_unlock(&philo->infos->mutex);
	}
	printf("is eating%s\n", END);
}

void	print_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->mutex);
	philo->infos->thr_alive = FALSE;
	pthread_mutex_unlock(&philo->infos->mutex);
	printf("died%s\n", END);
}

void	print_message(t_philo *philo, int type)
{
	pthread_mutex_lock(&philo->infos->mutex_message);
	pthread_mutex_lock(&philo->infos->mutex);
	if ((philo->infos->thr_alive == FALSE || philo->infos->all_eaten == TRUE)
		&& pthread_mutex_unlock(&philo->infos->mutex) == 0
		&& pthread_mutex_unlock(&philo->infos->mutex_message) == 0)
		return ;
	pthread_mutex_unlock(&philo->infos->mutex);
	printf("%s%lli %i ", set_color(type), get_time() - philo->infos->time_start,
		philo->id);
	if (type == FORK)
		printf("has taken a fork%s\n", END);
	else if (type == EAT)
	{
		if (philo->infos->must_eat != -1)
			print_eating(philo);
		else
			printf("is eating%s\n", END);
	}
	else if (type == SLEEP)
		printf("is sleeping%s\n", END);
	else if (type == THINK)
		printf("is thinking%s\n", END);
	else
		print_died(philo);
	pthread_mutex_unlock(&philo->infos->mutex_message);
}
