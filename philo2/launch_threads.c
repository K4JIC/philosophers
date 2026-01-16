/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:20:22 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/11 16:55:37 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	launch_one_thread(t_master *master, int philo_num)
{
	if (pthread_create(&(master->philo_threads[philo_num]),
						NULL,
						philo_routine,
						&(master->philos_info[philo_num]))
		== FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	launch_grim_reaper_thread(t_master *master)
{
	if (pthread_create(master->grim_reaper_thread,
						NULL,
						grim_reaper_routine,
						(void *)&(master->grim_info))
		== FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	launch_threads(t_master *master)
{
	int	i;

	if (launch_grim_reaper_thread(master) == FAILURE)
		return (FAILURE);
	printf("b\n");
	i = 0;
	while (i < master->input_info.philo_max)
	{
		if (launch_one_thread(master, i) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
