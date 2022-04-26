/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:47:53 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 09:00:38 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	modified_usleep(unsigned long time, t_info *info)
{
	unsigned long	end;

	end = ft_get_time() + time / 1000;
	while (!info->dead)
	{
		if (end <= ft_get_time())
			break ;
		usleep(200);
	}
}
