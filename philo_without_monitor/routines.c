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

void	*philo_routine(void *info)
{
	t_philo_thread_info	*philo_info;
	int					res;

	philo_info = (t_philo_thread_info *)info;
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
			res = philo_eat(philo_info);
			if (res == GET_TIME_ERROR)
				return (gettime_error_inner_thread(), NULL);
			if (res == FAILURE)
				return (NULL);
		}
	}
	return (NULL);
}

// void	*grim_reaper_routine(void *grim_info_void)
// {
	// t_grim_reaper_thread_info	*grim_info;
	// int							i;
	// t_time_us					now_clock_us;
	// t_time_us					hungry_time_us;
//
	// grim_info = (t_grim_reaper_thread_info *)grim_info_void;
	// i = 0;
	// while (1)
	// {
		// if (get_time_us(&now_clock_us) == FAILURE)
			// return (NULL);
		// pthread_mutex_lock(grim_info->last_eat_clock_us->mu);
		// hungry_time_us = now_clock_us - grim_info->last_eat_clock_us->val[i];
		// pthread_mutex_unlock(grim_info->last_eat_clock_us->mu);
		// if (hungry_time_us > grim_info->time_to_die_us)
		// {
			// pthread_mutex_lock(grim_info->finish_flag_lock);
			// *grim_info->dead_philo_name = i;
			// pthread_mutex_unlock(grim_info->finish_flag_lock);
			// grim_info->term_time_us = now_clock_us - grim_info->start_clock_us;
			// break ;
		// }
		// i = (i + 1) % grim_info->philo_max;
	// }
	// return (NULL);
// }
//
