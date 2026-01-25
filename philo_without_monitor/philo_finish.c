/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:51:51 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/17 16:51:53 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_is_finished(t_philo_thread_info *philo_info)
{
	int	ret;

	pthread_mutex_lock(philo_info->finish_flag_lock);
	ret = *philo_info->finish_flag;
	pthread_mutex_unlock(philo_info->finish_flag_lock);
	if (ret == 1)
		return (1);
	return (0);
}

int	is_alive(t_philo_thread_info *philo_info)
{
	t_time_us	now_clock_us;
	t_time_us	hungry_time_us;

	if (get_time_us(&now_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	hungry_time_us = now_clock_us - *philo_info->last_eat_clock_us->val;
	if (hungry_time_us > philo_info->time_to_die_us)
	{
		*philo_info->death_flag = 1;
		return (0);
	}
	return (1);
}

int	is_full(t_philo_thread_info *philo_info)
{
	if (philo_info->eat_count >= philo_info->must_eat)
		return (1);
	return (0);
}

int	thread_is_finished(t_philo_thread_info *philo_info)
{
	int	isalive;

	isalive = is_alive(philo_info);
	if (isalive == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (is_full(philo_info) || !isalive)
	{
		pthread_mutex_lock(philo_info->finish_flag_lock);
		*philo_info->finish_flag = 1;
		pthread_mutex_unlock(philo_info->finish_flag_lock);
		return (1);
	}
	return (0);
}

int	is_finished(t_philo_thread_info *philo_info)
{
	if (thread_is_finished(philo_info))
		return (FAILURE);
	if (process_is_finished(philo_info))
		return (FAILURE);
	return (SUCCESS);
}
