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
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>


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
		if (is_finished(philo_info) == FAILURE)
			return (FAILURE);
		if (now_clock_us - start_clock_us > wait_time_us)
			break ;
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
	if (*philo_info->finish_flag == ALIVE)
		printf("%-4lld %d %s\n", time_us / 1000, philo_info->philo_num, msg);
	pthread_mutex_unlock(philo_info->write_lock);
	return (SUCCESS);
}

int	philo_try_to_take_forks(t_philo_thread_info *philo_info)
{
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;
	int				success;

	success = 0;
	if (philo_info->lfork_owner_lock < philo_info->rfork_owner_lock)
	{
		first_lock = philo_info->rfork_owner_lock;
		second_lock = philo_info->lfork_owner_lock;
	}
	else
	{
		first_lock = philo_info->rfork_owner_lock;
		second_lock = philo_info->lfork_owner_lock;
	}
	pthread_mutex_lock(first_lock);
	pthread_mutex_lock(second_lock);
	if (*philo_info->lfork_owner == NO_OWNER && *philo_info->rfork_owner == NO_OWNER)
	{
		success = 1;
		*philo_info->rfork_owner = philo_info->philo_num;
		*philo_info->lfork_owner = philo_info->philo_num;
	}
	pthread_mutex_unlock(second_lock);
	pthread_mutex_unlock(first_lock);
	return (success);
}

void	philo_drop_forks(t_philo_thread_info *philo_info)
{
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;

	if (philo_info->lfork_owner_lock < philo_info->rfork_owner_lock)
	{
		first_lock = philo_info->rfork_owner_lock;
		second_lock = philo_info->lfork_owner_lock;
	}
	else
	{
		first_lock = philo_info->rfork_owner_lock;
		second_lock = philo_info->lfork_owner_lock;
	}
	pthread_mutex_lock(first_lock);
	pthread_mutex_lock(second_lock);
	*philo_info->lfork_owner = NO_OWNER;
	*philo_info->rfork_owner = NO_OWNER;
	pthread_mutex_unlock(second_lock);
	pthread_mutex_unlock(first_lock);

}

int	philo_wait_forks(t_philo_thread_info *philo_info)
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
		if (is_finished(philo_info) == FAILURE)
			return (FAILURE);
		if (philo_try_to_take_forks(philo_info) == 1)
			break ;
		usleep(UNIT_TIME_US);
		i++;
	}
	return (SUCCESS);
}

int	philo_take_forks(t_philo_thread_info *philo_info)
{
	if (philo_write(philo_info, "has taken a fork") == FAILURE)
		return (GET_TIME_ERROR);
	if (philo_write(philo_info, "has taken a fork") == FAILURE)
		return (GET_TIME_ERROR);
	return (SUCCESS);
}

int	philo_eat(t_philo_thread_info *philo_info)
{
	t_time_us	current_time;

	if (philo_write(philo_info, "is thinking") == FAILURE)
		return (GET_TIME_ERROR);
	if (philo_wait_forks(philo_info) == FAILURE)
		return (FAILURE);
	if (philo_take_forks(philo_info) == FAILURE)
		return (FAILURE);
	if (get_time_us(&current_time) == FAILURE)
		return (FAILURE);
	pthread_mutex_lock(philo_info->last_eat_lock);
	*philo_info->last_eat_clock_us = current_time;
	pthread_mutex_unlock(philo_info->last_eat_lock);
	if (philo_write(philo_info, "is eating") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_usleep(philo_info, philo_info->time_to_eat_us) == FAILURE)
	{
		philo_drop_forks(philo_info);
		return (FAILURE);
	}
	philo_info->eat_count++;
	philo_drop_forks(philo_info);
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
