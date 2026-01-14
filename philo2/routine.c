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


void	*philo_routine(void *info)
{
	t_thread_info	*tinfo;

	tinfo = (t_thread_info *)info;
	if (tinfo->philo_num % 2 == 0)
	{
		while (1)
		{
			if (philo_eat(tinfo) == FAILURE)
			{
				// philo_write(tinfo, "finish\n");
				return (NULL);
			}
			if (philo_sleep(tinfo) == FAILURE)
				return (NULL);
			if (philo_think(tinfo) == FAILURE)
				return (NULL);
		}
	}
	else
	{
		while (1)
		{
			if (philo_sleep(tinfo) == FAILURE)
			{
				// philo_write(tinfo, "finish\n");
				return (NULL);
			}
			if (philo_think(tinfo) == FAILURE)
				return (NULL);
			if (philo_eat(tinfo) == FAILURE)
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
				== GET_TIME_ERROR)
				return (NULL);
			return (NULL);
		}
		i = (i + 1) % philo_max;
		usleep(1);
	}
	return (NULL);
}
