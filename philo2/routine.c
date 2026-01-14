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
#include <unistd.h>

int	process_is_finished(t_thread_info *tinfo)
{
	int	ret;

	pthread_mutex_lock(tinfo->flag_lock);
	ret = *tinfo->finish_flag;
	pthread_mutex_unlock(tinfo->flag_lock);
	if (ret == 1)
		return (1);
	return (0);
}

int	is_alive(t_thread_info *tinfo)
{
	unsigned long long	hungry_time_us;

	if (get_time_duration_us(&hungry_time_us, tinfo->last_eat_us))
		return (GET_TIME_ERROR);
	if (hungry_time_us / 1000 > tinfo->time_to_die_ms)
	{
		*tinfo->Im_died = 1;
		return (0);
	}
	return (1);
}

int	is_full(t_thread_info *tinfo)
{
	if (tinfo->eat_count >= tinfo->must_eat)
		return (1);
	return (0);
}

int	thread_is_finished(t_thread_info *tinfo)
{
	int	isalive;

	isalive = is_alive(tinfo);
	if (isalive == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (is_full(tinfo) || !isalive)
	{
		pthread_mutex_lock(tinfo->flag_lock);
		*tinfo->finish_flag = 1;
		pthread_mutex_unlock(tinfo->flag_lock);
		return (1);
	}
	return (0);
}

int	is_finished(t_thread_info *tinfo)
{
	if (thread_is_finished(tinfo))
		return (FAILURE);
	if (process_is_finished(tinfo))
		return (FAILURE);
	return (SUCCESS);
}

int	philo_wait(t_thread_info *tinfo, time_t time)
{
	time_t	i;
	int		isfinished;

	i = 0;
	while (i < time)
	{
		isfinished = is_finished(tinfo);
		if (isfinished == GET_TIME_ERROR)
			return (GET_TIME_ERROR);
		if (isfinished)
			return (FAILURE);
		usleep(1);
		i++;
	}
	return (SUCCESS);
}

int	philo_write(t_thread_info *tinfo, char *msg)
{
	unsigned long long	time_us;

	if (get_time_duration_us(&time_us, tinfo->start_time_us) == FAILURE)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(tinfo->write_lock);
	printf("%04lld %d %s\n", time_us / 1000, tinfo->philo_num, msg);
	pthread_mutex_unlock(tinfo->write_lock);
	return (SUCCESS);
}

int	philo_eat(t_thread_info *tinfo)
{
	int	wait_ret;

	pthread_mutex_lock(tinfo->rfork_lock);
	if (philo_write(tinfo, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	pthread_mutex_lock(tinfo->lfork_lock);
	if (get_time_duration_us(&tinfo->last_eat_us, tinfo->start_time_us) == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(tinfo, "has taken a fork") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (philo_write(tinfo, "is eating") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	wait_ret = philo_wait(tinfo, tinfo->time_to_eat_ms * 1000);
	if (wait_ret == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (wait_ret == FAILURE)
		return (FAILURE);
	tinfo->eat_count++;
	pthread_mutex_unlock(tinfo->rfork_lock);
	pthread_mutex_unlock(tinfo->lfork_lock);
	return (SUCCESS);
}

int	philo_sleep(t_thread_info *tinfo)
{
	int	wait_ret;

	if (philo_write(tinfo, "is sleeping") == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	wait_ret = philo_wait(tinfo, tinfo->time_to_sleep_ms * 1000);
	if (wait_ret == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (wait_ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	philo_think(t_thread_info *tinfo)
{
	int	wait_ret;

	if (philo_write(tinfo, "is thinking") == FAILURE)
		return (FAILURE);
	wait_ret = philo_wait(tinfo, tinfo->time_to_think_ms * 1000);
	if (wait_ret == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (wait_ret == FAILURE)
		return (FAILURE);
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
			philo_write(tinfo, "a\n");
			if (philo_sleep(tinfo) == FAILURE)
				return (NULL);
			philo_write(tinfo, "b\n");
			if (philo_think(tinfo) == FAILURE)
				return (NULL);
			philo_write(tinfo, "c\n");
		}
	}
	else
	{
		while (1)
		{
			if (philo_sleep(tinfo) == FAILURE)
				return (NULL);
			philo_write(tinfo, "b\n");
			if (philo_think(tinfo) == FAILURE)
				return (NULL);
			philo_write(tinfo, "c\n");
			if (philo_eat(tinfo) == FAILURE)
				return (NULL);
			philo_write(tinfo, "a\n");
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
				== GET_TIME_ERROR)
				return (NULL);
			return (NULL);
		}
		i = (i + 1) % philo_max;
		usleep(1);
	}
	return (NULL);
}
