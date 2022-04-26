/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:47:58 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 10:00:00 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	incorrect_arguments(void)
{
	printf("Incorrect number of arguments.\n");
	printf("Input arguments: 1.number_of_philosophers, 2.time_to_die, ");
	printf("3.time_to_eat, 4.time_to_sleep, ");
	printf("5.[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

int	error_msg(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	*error_in_creation(t_info *info)
{
	pthread_mutex_lock(&info->printing);
	printf("Error in creating or detaching threads in launcher");
	pthread_mutex_unlock(&info->death_track);
	return (0);
}

int	error_in_creation_2(t_info *info)
{
	pthread_mutex_lock(&info->printing);
	printf("Error in creating or detaching threads in launcher");
	pthread_mutex_unlock(&info->death_track);
	return (0);
}

void	print_status(t_philo *philo, char *msg, int death)
{
	pthread_mutex_lock(&philo->info->printing);
	if (!philo->info->dead)
		printf("%lu %d %s\n", ft_get_time() - philo->info->starting_time,
			philo->number, msg);
	if (death)
	{
		philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->death_track);
	}
	pthread_mutex_unlock(&philo->info->printing);
}
