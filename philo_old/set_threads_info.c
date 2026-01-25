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

static void	set_one_thread_info(t_master *master, int philo_num,
	t_time_us start_clock_us)
{
	t_philo_thread_info	*philo_info;

	philo_info = &master->philos_info[philo_num];
	memset(philo_info, 0, sizeof(t_philo_thread_info));
	philo_info->start_clock_us = start_clock_us;
	philo_info->last_eat_clock_us = &master->last_eat_clock_us[philo_num];
	*philo_info->last_eat_clock_us = start_clock_us;
	philo_info->philo_num = philo_num + 1;
	philo_info->philo_max = master->input_info.philo_max;
	philo_info->time_to_die_us = master->input_info.time_to_die_us;
	philo_info->time_to_eat_us = master->input_info.time_to_eat_us;
	philo_info->time_to_sleep_us = master->input_info.time_to_sleep_us;
	philo_info->must_eat_option = master->must_eat_option;
	philo_info->must_eat = master->input_info.philo_must_eat;
	philo_info->full_philo_count = &master->full_philo_count;
	philo_info->finish_flag = &master->finish_flag;
}

static void	set_one_thread_mutex_info(t_master *master, int philo_num)
{
	t_philo_thread_info	*philo_info;

	philo_info = &master->philos_info[philo_num];
	philo_info->rfork_lock
		= &master->mutexes.forks_lock[philo_num
		% master->input_info.philo_max];
	philo_info->lfork_lock
		= &master->mutexes.forks_lock[(philo_num + 1)
		% master->input_info.philo_max];
	philo_info->write_lock = &master->mutexes.write_lock;
	philo_info->finish_flag_lock = &master->mutexes.finish_flag_lock;
	philo_info->last_eat_lock = &master->mutexes.last_eat_lock;
	philo_info->full_philo_lock = &master->mutexes.full_philo_lock;
}

void	set_grim_reaper_info(t_master *master, t_time_us start_clock_us)
{
	t_grim_reaper_thread_info	*grim_info;

	grim_info = &master->grim_info;
	grim_info->philo_max = master->input_info.philo_max;
	grim_info->start_clock_us = start_clock_us;
	grim_info->time_to_die_us = master->input_info.time_to_die_us;
	grim_info->term_time_us = 0;
	grim_info->last_eat_clock_us = master->last_eat_clock_us;
	grim_info->last_eat_lock = &master->mutexes.last_eat_lock;
	grim_info->write_lock = &master->mutexes.write_lock;
	grim_info->full_philo_lock = &master->mutexes.full_philo_lock;
	grim_info->full_philo_count = &master->full_philo_count;
	grim_info->dead_philo_name = &master->dead_philo_name;
	grim_info->finish_flag_lock = &master->mutexes.finish_flag_lock;
	grim_info->finish_flag = &master->finish_flag;
}

int	set_threads_info(t_master *master)
{
	t_time_us	start_clock_us;
	int			i;

	if (get_time_us(&start_clock_us) == FAILURE)
		return (FAILURE);
	set_grim_reaper_info(master, start_clock_us);
	i = 0;
	while (i < master->input_info.philo_max)
	{
		set_one_thread_info(master, i, start_clock_us);
		set_one_thread_mutex_info(master, i);
		i++;
	}
	return (SUCCESS);
}
