/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:17:39 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/13 16:28:52 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lonly_philo_routine(t_philo_thread_info *philo_info)
{
	int	res;

	res = lonly_philo_sleep(philo_info);
	if (res == GET_TIME_ERROR)
		return (gettime_error(), NULL);
	return (NULL);
}

static void	*odd_philo_routine(t_philo_thread_info *philo_info)
{
	int	res;

	res = philo_think(philo_info, 2);
	if (res == GET_TIME_ERROR)
		return (NULL);
	while (1)
	{
		res = philo_eat(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_sleep(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_think(philo_info, 1);
		if (res == GET_TIME_ERROR)
			return (gettime_error(), NULL);
		if (res == FAILURE)
			return (NULL);
	}
	return (NULL);
}

static void	*even_philo_routine(t_philo_thread_info *philo_info)
{
	int	res;

	while (1)
	{
		res = philo_sleep(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_think(philo_info, 1);
		if (res == GET_TIME_ERROR)
			return (gettime_error(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_eat_rev(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error(), NULL);
		if (res == FAILURE)
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *info)
{
	t_philo_thread_info	*philo_info;

	philo_info = (t_philo_thread_info *)info;
	if (philo_info->philo_max == 1)
		return (lonly_philo_routine(philo_info));
	if (philo_info->philo_num % 2 == 0)
		return (odd_philo_routine(philo_info));
	else
		return (even_philo_routine(philo_info));
}
