/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 10:49:25 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/25 17:03:47 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_usleep(t_philo_thread_info *philo_info, useconds_t wait_time_us)
{
	t_time_us	start_clock_us;
	t_time_us	now_clock_us;
	size_t		i;

	if (get_time_us(&start_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	i = 0;
	while (1)
	{
		if (get_time_us(&now_clock_us) == FAILURE)
			return (GET_TIME_ERROR);
		if (now_clock_us - start_clock_us > wait_time_us)
			break ;
		if (is_finished(philo_info) == FAILURE)
			return (FAILURE);
		usleep(UNIT_TIME_US);
		i++;
	}
	return (SUCCESS);
}

int	philo_write(t_philo_thread_info *philo_info, char *msg)
{
	t_time_us	time_us;
	int			res;

	if (get_time_duration_us(&time_us, philo_info->start_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->finish_flag_lock);
	res = *philo_info->finish_flag;
	pthread_mutex_unlock(philo_info->finish_flag_lock);
	if (res == FLAG_INIT)
	{
		pthread_mutex_lock(philo_info->write_lock);
		printf("%-4lld %d %s\n", time_us / 1000, philo_info->philo_num, msg);
		pthread_mutex_unlock(philo_info->write_lock);
	}
	return (SUCCESS);
}
