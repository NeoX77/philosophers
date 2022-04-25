/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:27:30 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 17:09:55 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define GREY	"\033[90m"
#define RED		"\033[91m"
#define GREEN	"\033[92m"
#define YELLOW	"\033[93m"
#define CYAN	"\033[96m"
#define END		"\033[0m"

char	*set_color(int type)
{
	if (type == FORK)
		return (GREY);
	else if (type == EAT)
		return (GREEN);
	else if (type == SLEEP)
		return (YELLOW);
	else if (type == THINK)
		return (CYAN);
	else
		return (RED);
}

void	print_message(t_philo *philo, int type)
{
	printf("%s%lli %i ", set_color(type), get_time() - philo->time_start,
		philo->id);
	if (type == FORK)
		printf("has taken a fork\n%s", END);
	else if (type == EAT)
		printf("is eating\n%s", END);
	else if (type == SLEEP)
		printf("is sleeping\n%s", END);
	else if (type == THINK)
		printf("is thinking\n%s", END);
	else
		printf("died\n%s", END);
}
