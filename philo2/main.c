/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:09:42 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/09 19:58:17 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	wait_threads(t_master master)
{
	int	i;

	i = 0;
	while (i < master.iinfo.philo_max)
	{
		pthread_detach(master.threads[i]);
//		pthread_join(master.threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_master	master;

	memset(&master, 0, sizeof(t_master));
	if (argc != 5 && argc != 6)
		return (input_error(&master));
	if (set_argv(argc, argv, &master.iinfo) == FAIL)
		return (input_error(&master));
	if (set_malloc(&master) == FAIL)
		return (malloc_error(&master));
	set_mutexes(&master.mutexes, master.iinfo.philo_max);
	if (set_threads_info(&master) == FAIL)
		return (gettime_error(&master));
	if (launch_threads(&master) == FAIL)
		return (threads_error(&master));
	wait_threads(master);
	pthread_join(*master.observe_thread, NULL);
	destroy_mutexes(&master.mutexes, master.iinfo.philo_max);
	free_master(&master);
}
