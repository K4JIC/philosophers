/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:09:42 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/13 17:07:51 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdio.h>

void	wait_threads(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->iinfo.philo_max)
	{
		pthread_join(master->threads[i], NULL);
		i++;
	}
}

void	report_death(t_master *master)
{
	int	philo_num;

	philo_num = 0;
	while (master->someone_died[philo_num] != 0 && philo_num < master->iinfo.philo_max)
		philo_num++;
	if (philo_num != master->iinfo.philo_max)
		printf("%04lld %d is died\n", master->term_time_us / 1000, philo_num);
}

int	main(int argc, char **argv)
{
	t_master	master;

	memset(&master, 0, sizeof(t_master));
	if (argc != 5 && argc != 6)
		return (input_error(&master));
	if (set_argv(argc, argv, &master.iinfo) == FAILURE)
		return (input_error(&master));
	if (set_malloc(&master) == FAILURE)
		return (malloc_error(&master));
	set_mutexes(&master.mutexes, master.iinfo.philo_max);
	if (set_threads_info(&master) == FAILURE)
		return (gettime_error(&master));
	if (launch_threads(&master) == FAILURE)
		return (threads_error(&master));
	wait_threads(&master);
	pthread_join(*master.observe_thread, NULL);
	report_death(&master);
	destroy_mutexes(&master.mutexes, master.iinfo.philo_max);
	free_master(&master);
}
