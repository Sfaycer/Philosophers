/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:47:55 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 08:11:24 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->eating);
	print_status(philo, "is eating", 0);
	philo->limit_time = ft_get_time() + philo->info->time_to_die;
	pthread_mutex_unlock(&philo->eating);
	modified_usleep(philo->info->time_to_eat * 1000, philo->info);
	if (philo->meals_to_have)
		philo->meals_to_have--;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
