/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_thread_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:58:12 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/28 21:00:32 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_one_thread_info(t_thread_info *tinfo, t_master *master,
		int philo_num, struct timeval start_time)
{
	tinfo->start_time = start_time;
	tinfo->philo_num = philo_num;
	tinfo->philo_max = master->iinfo.philo_max;
	tinfo->time_to_die = master->iinfo.time_to_die;
	tinfo->time_to_eat = master->iinfo.time_to_eat;
	tinfo->time_to_sleep = master->iinfo.time_to_sleep;
	tinfo->time_to_think = tinfo->time_to_die - tinfo->time_to_eat
						- tinfo->time_to_sleep;
	tinfo->rfork_lock =
		&master->mutexes.forks_lock[philo_num % master->iinfo.philo_max];
	tinfo->lfork_lock =
		&master->mutexes.forks_lock[(philo_num + 1) % master->iinfo.philo_max];
	tinfo->write_lock = &master->mutexes.write_lock;
	tinfo->death_lock = &master->mutexes.death_lock;
	return (SUCCESS);
}

int	set_threads_info(t_master *master)
{
	struct timeval	start_time;
	int				i;

	if (gettimeofday(&start_time, NULL) == -1)
		return (FAIL);
	i = 0;
	while (i < master->iinfo.philo_max)
	{
		set_one_thread_info(&master->threads_info[i], master, i, start_time);
		i++;
	}
	return (SUCCESS);
}


