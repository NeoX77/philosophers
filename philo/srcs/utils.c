/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:28:40 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/25 13:51:23 by wdebotte         ###   ########.fr       */
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
