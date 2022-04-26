/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 09:58:48 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 10:00:57 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_create(void *arg, void *(*func)(void *))
{
	pthread_t	tid;

	if (pthread_create(&tid, 0, func, arg))
		return (1);
	if (pthread_detach(tid))
		return (1);
	return (0);
}

static void	*meals_checker_thread(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (!info->sated && !info->dead)
	{
		i = 0;
		while (!info->philo[i].meals_to_have && i < info->phil_num)
			i++;
		if (i == info->phil_num)
		{
			pthread_mutex_lock(&info->printing);
			printf("Everyone ate their fill --- END\n");
			info->sated = 1;
			info->dead = 1;
			pthread_mutex_unlock(&info->death_track);
			pthread_mutex_unlock(&info->printing);
		}
	}
	return (0);
}

static void	*cycle_of_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->limit_time = ft_get_time() + philo->info->time_to_die;
	while (!philo->info->dead)
	{
		philo_eat(philo);
		if (philo->info->sated)
			break ;
		print_status(philo, "is sleeping", 0);
		modified_usleep(philo->info->time_to_sleep * 1000, philo->info);
		print_status(philo, "is thinking", 0);
	}
	return (0);
}

static void	*death_tracking(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	i = 0;
	while (i < info->phil_num && !info->dead)
	{
		pthread_mutex_lock(&info->philo[i].eating);
		if (ft_get_time() > info->philo[i].limit_time)
			print_status(&info->philo[i], "died", 1);
		pthread_mutex_unlock(&info->philo[i].eating);
		i++;
		i = i % info->phil_num;
	}
	return (0);
}

int	thread_launcher(void *arg)
{
	t_philo	*philo;
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	info->starting_time = ft_get_time();
	i = 0;
	while (i < info->phil_num)
	{
		philo = &info->philo[i];
		if (pthread_create(&philo->tid, 0, cycle_of_life, philo))
			return (error_in_creation_2(info));
		usleep(100);
		i++;
	}
	if (thread_create(info, death_tracking))
		return (error_in_creation_2(info));
	if (info->need_meals > 0)
		if (thread_create(info, meals_checker_thread))
			return (error_in_creation_2(info));
	pthread_mutex_lock(&info->death_track);
	free_all(info);
	return (0);
}
