/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:17:39 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/10 19:28:40 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

unsigned long long	get_time_us(t_thread_info *tinfo)
{
	struct timeval		tv;
	unsigned long long	time_us;

	if (gettimeofday(&tv, NULL) == -1)
		return (0); //後で書く
	time_us = (tv.tv_sec * SEC_USEC + tv.tv_usec)
		- (tinfo->start_time.tv_sec * SEC_USEC + tinfo->start_time.tv_usec);
	return (time_us);
}

void	philo_write(t_thread_info *tinfo, char *msg)
{
	unsigned long long	time_us;
	unsigned long long	time_ms;

	time_us = get_time_us(tinfo);
	time_ms = time_us / 1000;
	pthread_mutex_lock(tinfo->write_lock);
	printf("%04lld %d %s\n", time_ms, tinfo->philo_num, msg);
	pthread_mutex_unlock(tinfo->write_lock);
}

int	check_alive(t_thread_info *tinfo)
{
	unsigned long long	now_time_us;
	unsigned long long	hungry_time_us;

	now_time_us = get_time_us(tinfo);
	hungry_time_us = now_time_us - tinfo->last_eat;
	/*
	pthread_mutex_lock(tinfo->write_lock);
	printf("%d is hungry in %lld ms\n", tinfo->philo_num, hungry_time_us / 1000);
	pthread_mutex_unlock(tinfo->write_lock);
	*/
	if (hungry_time_us / 1000 < tinfo->time_to_die_ms)
		;
	else
	{
		*tinfo->Im_died = 1;
		philo_write(tinfo, "died");
		return (FAIL);
	}
	return (SUCCESS);
}

void	philo_eat(t_thread_info *tinfo)
{
	pthread_mutex_lock(tinfo->rfork_lock);
	philo_write(tinfo, "has taken a fork");
	if (check_alive(tinfo) == FAIL)
		return ;
	pthread_mutex_lock(tinfo->lfork_lock);
	tinfo->last_eat = get_time_us(tinfo);
	philo_write(tinfo, "has taken a fork");
	if (check_alive(tinfo) == FAIL)
		return ;
	philo_write(tinfo, "is eating");
	usleep(tinfo->time_to_eat_ms * 1000);
	pthread_mutex_unlock(tinfo->rfork_lock);
	pthread_mutex_unlock(tinfo->lfork_lock);
}

void	philo_sleep(t_thread_info *tinfo)
{
	philo_write(tinfo, "is sleeping");
	usleep(tinfo->time_to_sleep_ms * 1000);
}

void	philo_think(t_thread_info *tinfo)
{
	philo_write(tinfo, "is thinking");
	usleep(tinfo->time_to_think_ms * 1000);
}

void	*philo_routine(void *info)
{
	t_thread_info	*tinfo;

	tinfo = (t_thread_info *)info;
	if (tinfo->philo_num % 2 == 0)
	{
		while (1)
		{
			philo_eat(tinfo);
			if (check_alive(tinfo) == FAIL)
				return (NULL);
			philo_sleep(tinfo);
			if (check_alive(tinfo) == FAIL)
				return (NULL);
			philo_think(tinfo);
			if (check_alive(tinfo) == FAIL)
				return (NULL);
		}
	}
	else
	{
		while (1)
		{
			philo_sleep(tinfo);
			if (check_alive(tinfo) == FAIL)
				return (NULL);
			philo_think(tinfo);
			if (check_alive(tinfo) == FAIL)
				return (NULL);
			philo_eat(tinfo);
			if (check_alive(tinfo) == FAIL)
				return (NULL);
		}
	}
	return (NULL);
}
