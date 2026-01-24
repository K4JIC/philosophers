/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:09:42 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/17 16:52:42 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->input_info.philo_max)
	{
		pthread_join(master->philo_threads[i], NULL);
		i++;
	}
}

void	report_death(t_master *master)
{
	if (master->dead_philo_name != FLAG_INIT)
		printf("%04lld %d died\n", master->grim_info.term_time_us / 1000,
			master->dead_philo_name + 1);
}

int	main(int argc, char **argv)
{
	t_master	master;

	memset(&master, 0, sizeof(t_master));
	master.dead_philo_name = FLAG_INIT;
	master.finish_flag = FLAG_INIT;
	if (argc != 5 && argc != 6)
		return (input_error(&master));
	if (argc == 6)
		master.must_eat_option = 1;
	if (set_argv(argc, argv, &master.input_info) == FAILURE)
		return (input_error(&master));
	if (set_malloc(&master) == FAILURE)
		return (malloc_error(&master));
	set_mutexes(&master.mutexes, master.input_info.philo_max);
	if (set_threads_info(&master) == FAILURE)
		return (free_master(&master), gettime_error(&master));
	if (launch_threads(&master) == FAILURE)
	{
		destroy_mutexes(&master.mutexes, master.input_info.philo_max);
		free_master(&master);
		return (threads_error(&master));
	}
	wait_threads(&master);
	pthread_join(*master.grim_reaper_thread, NULL);
	report_death(&master);
	destroy_mutexes(&master.mutexes, master.input_info.philo_max);
	free_master(&master);
}
