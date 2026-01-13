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
#include <stdio.h>
#include <unistd.h>

int	philo_write(t_thread_info *tinfo, char *msg)
{
	unsigned long long	time_us;
	unsigned long long	time_ms;

	if (get_time_duration_us(&time_us, tinfo->start_time_us) == FAILURE)
		return (FAILURE);
	time_ms = time_us / 1000;
	pthread_mutex_lock(tinfo->write_lock);
	printf("%04lld %d %s\n", time_ms, tinfo->philo_num, msg);
	pthread_mutex_unlock(tinfo->write_lock);
	return (SUCCESS);
}

int	check_alive(t_thread_info *tinfo)
{
	unsigned long long	now_time_us;
	unsigned long long	hungry_time_us;

	if (get_time_duration_us(&now_time_us, tinfo->start_time_us) == FAILURE)
		return (FAILURE);
	hungry_time_us = now_time_us - tinfo->last_eat_us;
	if (hungry_time_us / 1000 > (unsigned long long)tinfo->time_to_die_ms)
	{
		*tinfo->Im_died = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	philo_eat(t_thread_info *tinfo)
{
	pthread_mutex_lock(tinfo->rfork_lock);
	if (philo_write(tinfo, "has taken a fork") == FAILURE)
		return (FAILURE);
	if (check_alive(tinfo) == FAILURE)
		return (FAILURE);
	pthread_mutex_lock(tinfo->lfork_lock);
	if (get_time_duration_us(&tinfo->last_eat_us, tinfo->start_time_us) == FAILURE)
		return (FAILURE);
	if (philo_write(tinfo, "has taken a fork") == FAILURE)
		return (FAILURE);
	if (check_alive(tinfo) == FAILURE)
		return (FAILURE);
	if (philo_write(tinfo, "is eating") == FAILURE)
		return (FAILURE);
	usleep(tinfo->time_to_eat_ms * 1000);
	pthread_mutex_unlock(tinfo->rfork_lock);
	pthread_mutex_unlock(tinfo->lfork_lock);
	return (SUCCESS);
}

int	philo_sleep(t_thread_info *tinfo)
{
	if (philo_write(tinfo, "is sleeping") == FAILURE)
		return (FAILURE);
	usleep(tinfo->time_to_sleep_ms * 1000);
	return (SUCCESS);
}

int	philo_think(t_thread_info *tinfo)
{
	if (philo_write(tinfo, "is thinking") == FAILURE)
		return (FAILURE);
	usleep(tinfo->time_to_think_ms * 1000);
	return (SUCCESS);
}

void	*philo_routine(void *info)
{
	t_thread_info	*tinfo;

	tinfo = (t_thread_info *)info;
	if (tinfo->philo_num % 2 == 0)
	{
		while (1)
		{
			if (philo_eat(tinfo) == FAILURE)
				return (NULL);
			if (check_alive(tinfo) == FAILURE)
				return (NULL);
			if (philo_sleep(tinfo) == FAILURE)
				return (NULL);
			if (check_alive(tinfo) == FAILURE)
				return (NULL);
			if (philo_think(tinfo) == FAILURE)
				return (NULL);
			if (check_alive(tinfo) == FAILURE)
				return (NULL);
		}
	}
	else
	{
		while (1)
		{
			if (philo_sleep(tinfo) == FAILURE)
				return (NULL);
			if (check_alive(tinfo) == FAILURE)
				return (NULL);
			if (philo_think(tinfo) == FAILURE)
				return (NULL);
			if (check_alive(tinfo) == FAILURE)
				return (NULL);
			if (philo_eat(tinfo) == FAILURE)
				return (NULL);
			if (check_alive(tinfo) == FAILURE)
				return (NULL);
		}
	}
	return (NULL);
}

void	*observe_routine(void *master_void)
{
	t_master	*master;
	int			philo_max;
	int			i;

	master = (t_master *)master_void;
	philo_max = master->iinfo.philo_max;
	i = 0;
	while (1)
	{
		if (master->someone_died[i] != 0)
		{
			if (get_time_duration_us(&master->term_time_us,
									master->threads_info->start_time_us)
				== FAILURE)
				return (NULL);
			return (NULL);
		}
		i = (i + 1) % philo_max;
		usleep(1);
	}
	return (NULL);
}
