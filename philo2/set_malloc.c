/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:18:39 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/11 16:50:46 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "philo.h"

void	*ft_calloc(size_t memsize)
{
	void	*heap_area;

	heap_area = malloc(memsize);
	if (!heap_area)
		return (NULL);
	memset(heap_area, 0, memsize);
	return (heap_area);
}

int	set_malloc(t_master *master)
{
	if (!master->iinfo.philo_max)
		return (FAILURE);
	master->threads = ft_calloc(sizeof(pthread_t) *
						master->iinfo.philo_max);
	if (!master->threads)
		return (FAILURE);
	master->observe_thread = ft_calloc(sizeof(pthread_t));
	if (!master->observe_thread)
		return (free_master(master), FAILURE);
	master->threads_info = ft_calloc(sizeof(t_thread_info) *
						master->iinfo.philo_max);
	if (!master->threads_info)
		return (free_master(master), FAILURE);
	master->mutexes.forks_lock = ft_calloc(sizeof(pthread_mutex_t) *
						master->iinfo.philo_max);
	if (!master->mutexes.forks_lock)
		return (free_master(master), FAILURE);
	master->someone_died = ft_calloc(sizeof(int) *
						master->iinfo.philo_max);
	if (!master->someone_died)
		return (free_master(master), FAILURE);
	return (SUCCESS);
}

void	free_master(t_master *master)
{
	if (master->threads)
		free(master->threads);
	if (master->observe_thread)
		free(master->observe_thread);
	if (master->threads_info)
		free(master->threads_info);
	if (master->mutexes.forks_lock)
		free(master->mutexes.forks_lock);
	if (master->someone_died)
		free(master->someone_died);
}
