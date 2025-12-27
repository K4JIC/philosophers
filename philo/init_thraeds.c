/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thraeds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:26:24 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/27 17:15:38 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * prepare information to launch thread.
 * receive "t_input_info input_info".
 * pack input_info and mutexes in "t_thread_info thread_info".
 */

#include "philo.h"
#include <stdlib.h>

t_thread_info	*pack_thread_info(t_input_info iinfo,
								pthread_mutex_t right_fork,
								pthread_mutex_t left_fork,
								t_mutexes mutexes)
{
	t_thread_info	*tinfo;

	tinfo = (t_thread_info *)malloc(sizeof(t_thread_info));
	if (!tinfo)
		return (NULL);
	tinfo->time_to_die = iinfo.time_to_die;
	tinfo->time_to_eat = iinfo.time_to_eat;
	tinfo->time_to_sleep = iinfo.time_to_sleep;
	tinfo->time_to_think = iinfo.time_to_die -
	(iinfo.time_to_eat + iinfo.time_to_sleep);
	tinfo->right_fork = right_fork;
	tinfo->left_fork = left_fork;
	tinfo->tty = mutexes.tty;
	return (tinfo);
}

int	launch_one_thread(pthread_t thread, int thread_num, t_input_info iinfo, t_mutexes mutexes)
{
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	t_thread_info	*tinfo;

	if (thread_num != 0)
		right_fork = mutexes.forks[thread_num];
	else
		right_fork = mutexes.forks[iinfo.philo_max];
	if (thread_num != iinfo.philo_max - 1)
		left_fork = mutexes.forks[thread_num + 1];
	else
		left_fork = mutexes.forks[0];
	tinfo = pack_thread_info(iinfo, right_fork, left_fork, mutexes);
	if (!tinfo)
		return (FAIL);
	if (pthread_create(thread, NULL, philosophers_routine, tinfo))
		return (FAIL);
	return (SUCCESS);
}

int	launch_threads(t_input_info iinfo, t_mutexes mutexes)
{
	int			thread_max;
	pthread_t	*threads;
	int			i;
	int			res;

	thread_max = iinfo.philo_max;
	threads = malloc(thread_max * sizeof(pthread_t));
	if (!threads)
		return (FAIL);
	i = 0;
	while (i < thread_max)
	{
		res = launch_one_thread(threads[i], i, iinfo, mutexes);
		if (res == FAIL)
			return (FAIL);
		i++;
	}
}