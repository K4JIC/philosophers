/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:16:19 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/08 18:42:42 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

unsigned long long	get_time_us(t_thread_info tinfo)
{
	struct timeval		tv;
	unsigned long long	utime;

	if (gettimeofday(&tv, NULL) == -1)
		return (0); //後で書く
	utime = (tv.tv_sec * SEC_USEC + tv.tv_usec)
		- (tinfo.start_time.tv_sec * SEC_USEC + tinfo.start_time.tv_usec);
	return (utime);
}

void	philo_write(t_thread_info tinfo, char *msg)
{
	unsigned long long	utime;
	unsigned long long	mtime;

	utime = get_time_us(tinfo);
	mtime = utime / 1000;
	pthread_mutex_lock(tinfo.write_lock);
	printf("%04lld %d %s\n", mtime, tinfo.philo_num, msg);
	pthread_mutex_unlock(tinfo.write_lock);
}

int	death_check(t_thread_info tinfo)
{
	unsigned long long	now_time_us;

	now_time_us = get_time_us(tinfo);
	if (now_time_us / 1000 < tinfo.time_to_die_ms)
	{
		
		pthread_mutex_lock(tinfo.death_lock);
		pthread_mutex_unlock(tinfo.death_lock);
	}
	else
	{
		pthread_mutex_lock(tinfo.death_lock);
		return (FAIL);
	}

}

void	philo_eat(t_thread_info tinfo)
{
	pthread_mutex_lock(tinfo.rfork_lock);
	philo_write(tinfo, "has taken a fork");
	pthread_mutex_lock(tinfo.lfork_lock);
	tinfo.last_eat = get_time_us(tinfo);
	philo_write(tinfo, "has taken a fork");
	philo_write(tinfo, "is eating");
	usleep(tinfo.time_to_eat_ms * 1000);
	pthread_mutex_unlock(tinfo.rfork_lock);
	pthread_mutex_unlock(tinfo.lfork_lock);
}

void	philo_sleep(t_thread_info tinfo)
{
	philo_write(tinfo, "is sleeping");
	usleep(tinfo.time_to_sleep_ms * 1000);
}

void	philo_think(t_thread_info tinfo)
{
	philo_write(tinfo, "is thinking");
	usleep(tinfo.time_to_think_ms * 1000);
}

void	*philo_routine(void *info)
{
	t_thread_info	tinfo;

	tinfo = *(t_thread_info *)info;
	if (tinfo.philo_num % 2 == 0)
	{
		while (1)
		{
			philo_eat(tinfo);
			philo_sleep(tinfo);
			philo_think(tinfo);
		}
	}
	else
	{
		while (1)
		{
			philo_sleep(tinfo);
			philo_eat(tinfo);
			philo_think(tinfo);
		}
	}
}
