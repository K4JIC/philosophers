/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_thread_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:58:12 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/10 13:56:59 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long long	ft_min(unsigned long long a, unsigned long long b, unsigned long long c)
{
	unsigned long long	min;

	min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return (min);
}

static void	set_one_thread_info(t_master *master,
		int philo_num, unsigned long long start_time_us)
{
	t_thread_info	*tinfo;

	tinfo = &master->threads_info[philo_num];
	memset(tinfo, 0, sizeof(t_thread_info));
	tinfo->start_time_us = start_time_us;
	tinfo->last_eat_us = start_time_us;
	tinfo->unit_time_us = ft_min(master->iinfo.time_to_die_us, master->iinfo.time_to_eat_us, master->iinfo.time_to_sleep_us);
	tinfo->philo_num = philo_num;
	tinfo->philo_max = master->iinfo.philo_max;
	tinfo->time_to_die_us = master->iinfo.time_to_die_us;
	tinfo->time_to_eat_us = master->iinfo.time_to_eat_us;
	tinfo->time_to_sleep_us = master->iinfo.time_to_sleep_us;
	tinfo->time_to_think_us = tinfo->time_to_die_us - tinfo->time_to_eat_us
						- tinfo->time_to_sleep_us - 1;
	if (tinfo->time_to_think_us < 0)
		tinfo->time_to_think_us = 0;
	tinfo->rfork_lock =
		&master->mutexes.forks_lock[philo_num % master->iinfo.philo_max];
	tinfo->lfork_lock =
		&master->mutexes.forks_lock[(philo_num + 1) % master->iinfo.philo_max];
	tinfo->write_lock = &master->mutexes.write_lock;
	tinfo->flag_lock = &master->mutexes.flag_lock;
	tinfo->Im_died = &master->someone_died[philo_num];
	tinfo->must_eat = master->philo_must_eat;
	tinfo->finish_flag = &master->finish_flag;
	tinfo->must_eat_option = master->must_eat_option;
}

int	set_threads_info(t_master *master)
{
	unsigned long long	start_time_us;
	int					i;

	if (get_time_us(&start_time_us) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < master->iinfo.philo_max)
	{
		set_one_thread_info(master, i, start_time_us);
		i++;
	}
	return (SUCCESS);
}
