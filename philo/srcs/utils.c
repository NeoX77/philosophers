/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:34:04 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/05 18:51:24 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
