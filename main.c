/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:47:25 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 10:19:03 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_info *info)
{
	int	i;

	i = 0;
	if (info->phil_num == 1)
		pthread_mutex_unlock(info->philo[0].left_fork);
	while (i < info->phil_num)
	{
		pthread_join(info->philo[i].tid, 0);
		i++;
	}
	i = 0;
	while (i < info->phil_num)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philo[i].eating);
		i++;
	}
	free(info->forks);
	free(info->philo);
	pthread_mutex_destroy(&info->death_track);
	pthread_mutex_destroy(&info->printing);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;
	pthread_t	tid;

	if (argc < 5 || argc > 6)
		return (incorrect_arguments());
	if (parse_arguments(&info, &philo, argv))
		return (1);
	if (thread_launcher(&info))
		return (1);
	return (0);
}
