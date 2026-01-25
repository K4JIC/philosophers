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

int	philo_eat(t_philo_thread_info *philo_info)
{
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

int	philo_eat_rev(t_philo_thread_info *philo_info)
{
	pthread_mutex_lock(philo_info->lfork_lock);
	if (philo_write(philo_info, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(philo_info->rfork_lock);
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

int	lonly_philo_sleep(t_philo_thread_info *philo_info)
{
	if (philo_write(philo_info, "is sleeping") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_usleep(philo_info, philo_info->time_to_sleep_us) == FAILURE)
		return (FAILURE);
	if (philo_write(philo_info, "is thinking") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_usleep(philo_info, philo_info->time_to_die_us + UNIT_TIME_US)
		== FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	philo_think(t_philo_thread_info *philo_info)
{
	t_time_us	time_to_think_us;

	if (philo_info->philo_max % 2 == 1)
	{
		time_to_think_us = UNIT_TIME_US;
		if (philo_write(philo_info, "is thinking") == GET_TIME_ERROR)
			return (GET_TIME_ERROR);
		if (philo_usleep(philo_info, time_to_think_us) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
