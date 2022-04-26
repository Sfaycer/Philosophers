/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_and_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 00:50:58 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/18 01:08:51 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_and_error(char *str, int *error)
{
	unsigned int	result;
	unsigned int	cutoff;

	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	cutoff = 214748364;
	result = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		if (result > cutoff || (result == cutoff && (*str - '0') > 7))
		{
			*error = 1;
			break ;
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str)
		*error = 1;
	return (result);
}
