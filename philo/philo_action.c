/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:51:43 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/17 16:51:48 by tozaki           ###   ########.fr       */
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

	if (get_time_duration_us(&time_us, philo_info->start_clock_us) == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->write_lock);
	if (*philo_info->dead_philo_name == -1)
		printf("%04lld %d %s\n", time_us / 1000, philo_info->philo_num, msg);
	pthread_mutex_unlock(philo_info->write_lock);
	return (SUCCESS);
}

int	philo_eat(t_philo_thread_info *philo_info)
{
	if (philo_write(philo_info, "is thinking") == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->rfork_lock);
	if (philo_write(philo_info, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->lfork_lock);
	pthread_mutex_lock(philo_info->last_eat_lock);
	if (get_time_us(philo_info->last_eat_clock_us) == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	pthread_mutex_unlock(philo_info->last_eat_lock);
	if (philo_write(philo_info, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(philo_info, "is eating") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_usleep(philo_info, philo_info->time_to_eat_us) == FAILURE)
	{
		pthread_mutex_unlock(philo_info->rfork_lock);
		pthread_mutex_unlock(philo_info->lfork_lock);
		return (FAILURE);
	}
	philo_info->eat_count++;
	pthread_mutex_unlock(philo_info->rfork_lock);
	pthread_mutex_unlock(philo_info->lfork_lock);
	return (SUCCESS);
}

int	philo_sleep(t_philo_thread_info *philo_info)
{
	if (philo_write(philo_info, "is sleeping") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_usleep(philo_info, philo_info->time_to_sleep_us) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	philo_think(t_philo_thread_info *philo_info)
{
	if (philo_write(philo_info, "is thinking") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_usleep(philo_info, philo_info->time_to_think_us) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
