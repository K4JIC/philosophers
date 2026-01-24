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
#include <pthread.h>

static void	*lonly_philo_routine(t_philo_thread_info *philo_info)
{
	int	res;

	res = lonly_philo_sleep(philo_info);
	if (res == GET_TIME_ERROR)
		return (gettime_error_inner_thread(), NULL);
	return (NULL);
}

static void	*odd_philo_routine(t_philo_thread_info *philo_info)
{
	int	res;

	while (1)
	{
		res = philo_eat(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error_inner_thread(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_sleep(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error_inner_thread(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_think(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error_inner_thread(), NULL);
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
			return (gettime_error_inner_thread(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_eat_rev(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error_inner_thread(), NULL);
		if (res == FAILURE)
			return (NULL);
		res = philo_think(philo_info);
		if (res == GET_TIME_ERROR)
			return (gettime_error_inner_thread(), NULL);
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

void	*grim_reaper_routine(void *grim_info_void)
{
	t_grim_reaper_thread_info	*grim_info;
	int							i;
	t_time_us					now_clock_us;
	t_time_us					last_eat_us;
	t_time_us					hungry_time_us;

	grim_info = (t_grim_reaper_thread_info *)grim_info_void;
	i = 0;
	while (1)
	{
		if (get_time_us(&now_clock_us) == FAILURE)
			return (NULL);
		pthread_mutex_lock(grim_info->last_eat_lock);
		last_eat_us = grim_info->last_eat_clock_us[i];
		pthread_mutex_unlock(grim_info->last_eat_lock);
		if (now_clock_us >= last_eat_us)
			hungry_time_us = now_clock_us - last_eat_us;
		else
			hungry_time_us = 0;
		if (hungry_time_us > grim_info->time_to_die_us)
		{
			*grim_info->dead_philo_name = i;
			*grim_info->finish_flag = FLAG_DONE;
			grim_info->term_time_us = now_clock_us - grim_info->start_clock_us;
			break ;
		}
		pthread_mutex_lock(grim_info->full_philo_lock);
		if (*grim_info->full_philo_count == grim_info->philo_max)
		{
			pthread_mutex_unlock(grim_info->full_philo_lock);
			*grim_info->finish_flag = FLAG_DONE;
			return (NULL);
		}
		pthread_mutex_unlock(grim_info->full_philo_lock);
		i = (i + 1) % grim_info->philo_max;
		usleep(1);
	}
	return (NULL);
}
