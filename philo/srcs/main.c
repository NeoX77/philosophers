/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:29:45 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/07 16:06:39 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo \t[number of philosophers]\n\t\t[time to die]\
\n\t\t[time to eat]\n\t\t[time to sleep]\n\t\t[number of how many time \
each philosopher must eat(optionnal)]\nAll time must be in ms!\n");
		return (1);
	}
}
