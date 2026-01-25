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
		printf("%-4lld %d died\n", master->grim_info.term_time_us / 1000,
			master->dead_philo_name + 1);
}

void	close_process(t_master *master)
{
	destroy_mutexes(&master->mutexes, master->input_info.philo_max);
	free_master(master);
}

int	main(int argc, char **argv)
{
	t_master	master;

	memset(&master, 0, sizeof(t_master));
	master.dead_philo_name = FLAG_INIT;
	master.finish_flag = FLAG_INIT;
	if (argc != 5 && argc != 6)
		return (input_error());
	if (argc == 6)
		master.must_eat_option = 1;
	if (set_argv(argc, argv, &master.input_info) == FAILURE)
		return (input_error());
	if (set_malloc(&master) == FAILURE)
		return (malloc_error());
	set_mutexes(&master.mutexes, master.input_info.philo_max);
	if (set_threads_info(&master) == FAILURE)
		return (close_process(&master), gettime_error());
	if (launch_threads(&master) == FAILURE)
	{
		close_process(&master);
		return (threads_error());
	}
	wait_threads(&master);
	pthread_join(*master.grim_reaper_thread, NULL);
	report_death(&master);
	close_process(&master);
}
