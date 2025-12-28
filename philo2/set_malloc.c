/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:18:39 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/28 20:43:19 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	set_malloc(t_master *master)
{
	if (!master->iinfo.philo_max)
		return (FAIL);
	master->threads = malloc(sizeof(pthread_t) *
						master->iinfo.philo_max);
	if (!master->threads)
		return (FAIL);
	master->threads_info = malloc(sizeof(t_thread_info) *
						master->iinfo.philo_max);
	if (!master->threads_info)
		return (free_master(master), FAIL);
	master->mutexes.forks_lock = malloc(sizeof(pthread_mutex_t) *
						master->iinfo.philo_max);
	if (!master->mutexes.forks_lock)
		return (free_master(master), FAIL);
	return (SUCCESS);
}

void	free_master(t_master *master)
{
	if (master->threads)
		free(master->threads);
	if (master->threads_info)
		free(master->threads_info);
	if (master->mutexes.forks_lock)
		free(master->mutexes.forks_lock);
}
