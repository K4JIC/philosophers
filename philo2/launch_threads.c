/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:20:22 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/10 14:35:51 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

/*
void	*philo_routine(void *info)
{
	t_thread_info	tinfo;

	tinfo = *(t_thread_info *)info;
	pthread_mutex_lock(tinfo.write_lock);
	printf("This is %d philo.\n", tinfo.philo_num);
	pthread_mutex_unlock(tinfo.write_lock);
}
*/

static int	launch_one_thread(t_master *master, int philo_num)
{
	if (pthread_create(&(master->threads[philo_num]),
						NULL,
						philo_routine,
						&(master->threads_info[philo_num]))
		== FAIL)
		return (FAIL);
	return (SUCCESS);
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
		while (master->someone_died[i])
		{
			if (master->someone_died[i] == 1)
				return (NULL);
			i = (i + 1) % philo_max;
		}
	}
	return (NULL);
}

static int	launch_observe_thread(t_master *master)
{
	if (pthread_create(master->observe_thread,
						NULL,
						observe_routine,
						(void *)master)
		== FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	launch_threads(t_master *master)
{
	int	i;

	if (launch_observe_thread(master) == FAIL)
		return (FAIL);
	i = 0;
	while (i < master->iinfo.philo_max)
	{
		if (launch_one_thread(master, i) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
