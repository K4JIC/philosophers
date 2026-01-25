/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:10:08 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/25 11:10:10 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_alive(t_grim_reaper_thread_info *grim_info, int philo_num)
{
	t_time_us					now_clock_us;
	t_time_us					last_eat_us;
	t_time_us					hungry_time_us;

	if (get_time_us(&now_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(grim_info->last_eat_lock);
	last_eat_us = grim_info->last_eat_clock_us[philo_num];
	pthread_mutex_unlock(grim_info->last_eat_lock);
	if (now_clock_us >= last_eat_us)
		hungry_time_us = now_clock_us - last_eat_us;
	else
		hungry_time_us = 0;
	if (hungry_time_us > grim_info->time_to_die_us)
	{
		*grim_info->dead_philo_name = philo_num;
		*grim_info->finish_flag = FLAG_DONE;
		grim_info->term_time_us = now_clock_us - grim_info->start_clock_us;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_full(t_grim_reaper_thread_info *grim_info)
{
	pthread_mutex_lock(grim_info->full_philo_lock);
	if (*grim_info->full_philo_count == grim_info->philo_max)
	{
		pthread_mutex_unlock(grim_info->full_philo_lock);
		*grim_info->finish_flag = FLAG_DONE;
		return (SUCCESS);
	}
	pthread_mutex_unlock(grim_info->full_philo_lock);
	return (FAILURE);
}

void	*grim_reaper_routine(void *grim_info_void)
{
	t_grim_reaper_thread_info	*grim_info;
	int							i;
	int							ret;

	grim_info = (t_grim_reaper_thread_info *)grim_info_void;
	i = 0;
	while (1)
	{
		ret = check_alive(grim_info, i);
		if (ret == GET_TIME_ERROR)
		{
			break ;
		}
		else if (ret == FAILURE)
			break ;
		if (check_full(grim_info) == SUCCESS)
			break ;
		i = (i + 1) % grim_info->philo_max;
		usleep(1);
	}
	return (NULL);
}
