/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:48:04 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 10:50:14 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

struct	s_info;

typedef struct s_philo
{
	int				number;
	int				meals_to_have;
	unsigned long	limit_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eating;
	struct s_info	*info;
	pthread_t		tid;
}				t_philo;

typedef struct s_info
{
	int				phil_num;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				need_meals;
	int				sated;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	pthread_mutex_t	death_track;
	unsigned long	starting_time;
	t_philo			*philo;
	int				dead;
}				t_info;

int				parse_arguments(t_info *info, t_philo **philo, char **argv);
int				ft_atoi_and_error(char *str, int *error);
void			philo_eat(t_philo *philo);
void			free_all(t_info *info);

// simulation.c
int				thread_launcher(void *arg);

// messages.c
int				incorrect_arguments(void);
int				error_msg(char *str);
void			*error_in_creation(t_info *info);
int				error_in_creation_2(t_info *info);
void			print_status(t_philo *philo, char *msg, int death);

// time.c
unsigned long	ft_get_time(void);
void			modified_usleep(unsigned long time, t_info *info);

#endif
