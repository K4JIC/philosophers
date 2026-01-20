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
#include <stdio.h>

void	*philo_routine(void *info)
{
	t_philo_thread_info	*philo_info;
	int					res;

	philo_info = (t_philo_thread_info *)info;
	// if (philo_info->philo_num == 0)
	// {
	// 	while (1)
	// 	{
	// 		res = philo_eat_rev(philo_info);
	// 		if (res == GET_TIME_ERROR)
	// 			return (gettime_error_inner_thread(), NULL);
	// 		if (res == FAILURE)
	// 			return (NULL);
	// 		res = philo_sleep(philo_info);
	// 		if (res == GET_TIME_ERROR)
	// 			return (gettime_error_inner_thread(), NULL);
	// 		if (res == FAILURE)
	// 			return (NULL);
	// 	}
	// }
	if (philo_info->philo_num % 2 == 0)
	{
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
		}
	}
	else
	{
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
		}
	}
	return (NULL);
}

// void	*observe_routine(void *master_void)
// {
// 	t_master	*master;
// 	int			philo_max;
// 	int			i;

// 	master = (t_master *)master_void;
// 	philo_max = master->input_info.philo_max;
// 	i = 0;
// 	while (1)
// 	{
// 		if (master->last_eat_clock_us[i] != 0)
// 		{
// 			if (get_time_duration_us(&master->term_time_us,
// 									master->philos_info->start_clock_us)
// 				== GET_TIME_ERROR)
// 				return (NULL);
// 			return (NULL);
// 		}
// 		i = (i + 1) % philo_max;
// 		usleep(1);
// 	}
// 	return (NULL);
// }

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
			pthread_mutex_lock(grim_info->write_lock);
			printf("hungry = %lld\n", hungry_time_us / 1000);
			pthread_mutex_unlock(grim_info->write_lock);
			pthread_mutex_lock(grim_info->death_note_lock);
			*grim_info->dead_philo_name = i;
			pthread_mutex_unlock(grim_info->death_note_lock);
			grim_info->term_time_us = now_clock_us - grim_info->start_clock_us;
			break ;
		}
		i = (i + 1) % grim_info->philo_max;
		usleep(1);
	}
	return (NULL);
}
