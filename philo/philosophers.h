/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:36:27 by wdebotte          #+#    #+#             */
/*   Updated: 2022/04/05 18:57:56 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

typedef struct	s_infos
{
	int	n_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	n_can_eat;
}	t_infos;

int	ft_atoi(char *str);

#endif
