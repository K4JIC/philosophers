/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:51:51 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/25 17:20:57 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	process_is_finished(t_philo_thread_info *philo_info)
{
	int	ret;

	pthread_mutex_lock(philo_info->finish_flag_lock);
	ret = *philo_info->finish_flag;
	pthread_mutex_unlock(philo_info->finish_flag_lock);
	if (ret != FLAG_INIT)
		return (1);
	return (0);
}

static int	is_full(t_philo_thread_info *philo_info)
{
	if (!philo_info->must_eat_option)
		return (0);
	if (philo_info->philo_finish_norma != 1)
	{
		if (philo_info->eat_count >= philo_info->must_eat)
		{
			philo_info->philo_finish_norma = 1;
			return (1);
		}
	}
	return (0);
}

int	is_finished(t_philo_thread_info *philo_info)
{
	if (process_is_finished(philo_info))
		return (FAILURE);
	if (is_full(philo_info))
	{
		pthread_mutex_lock(philo_info->full_philo_lock);
		*philo_info->full_philo_count += 1;
		pthread_mutex_unlock(philo_info->full_philo_lock);
		return (SUCCESS);
	}
	return (SUCCESS);
}