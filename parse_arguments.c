/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:55:57 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 10:23:47 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fill_basic_parameters(t_info *info, char **argv)
{
	int	error;

	error = 0;
	info->phil_num = ft_atoi_and_error(argv[1], &error);
	info->time_to_die = ft_atoi_and_error(argv[2], &error);
	info->time_to_eat = ft_atoi_and_error(argv[3], &error);
	info->time_to_sleep = ft_atoi_and_error(argv[4], &error);
	if (argv[5])
		info->need_meals = ft_atoi_and_error(argv[5], &error);
	else
		info->need_meals = -1;
	if (error)
		printf("Arguments should represent positive int and be digits\n");
	if (!error && (info->phil_num < 1 || info->phil_num > 200))
	{
		printf("Range of number_of_philosophers: 1-200\n");
		error = 1;
	}
	if (!error && (info->need_meals == 0))
	{
		printf("Number of times to eat should be > 0\n");
		error = 1;
	}
	return (error);
}

static int	init_philos(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->phil_num)
	{
		philo[i].number = i + 1;
		philo[i].meals_to_have = info->need_meals;
		philo[i].left_fork = &info->forks[i];
		philo[i].right_fork = &info->forks[(i + 1) % info->phil_num];
		philo[i].info = info;
		if (pthread_mutex_init(&philo[i].eating, 0))
			return (1);
		i++;
	}
	return (0);
}

static int	info_mutex_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->phil_num)
		if (pthread_mutex_init(&info->forks[i++], 0))
			return (1);
	if (pthread_mutex_init(&info->printing, 0))
		return (1);
	if (pthread_mutex_init(&info->death_track, 0))
		return (1);
	pthread_mutex_lock(&info->death_track);
	return (0);
}

int	parse_arguments(t_info *info, t_philo **philo, char **argv)
{
	if (fill_basic_parameters(info, argv))
		return (1);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->phil_num);
	if (!info->forks)
		return (error_msg("[Forks] malloc is unsuccesful"));
	*philo = (t_philo *)malloc(sizeof(t_philo) * info->phil_num);
	if (!*philo)
		return (error_msg("[Philo] malloc is unsuccesful"));
	info->philo = *philo;
	info->sated = 0;
	info->dead = 0;
	if (init_philos(info, *philo))
		return (error_msg("Mutex init error in initializing Philos"));
	if (info_mutex_init(info))
		return (error_msg("Mutex init error in initializing Info"));
	return (0);
}
