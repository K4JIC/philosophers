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
	if (!master->input_info.philo_max)
		return (FAILURE);
	master->philo_threads = ft_calloc(sizeof(pthread_t) *
						master->input_info.philo_max);
	if (!master->philo_threads)
		return (FAILURE);
	master->grim_reaper_thread = ft_calloc(sizeof(pthread_t));
	if (!master->grim_reaper_thread)
		return (free_master(master), FAILURE);
	master->philos_info = ft_calloc(sizeof(t_philo_thread_info) *
						master->input_info.philo_max);
	if (!master->philos_info)
		return (free_master(master), FAILURE);
	master->mutexes.forks_lock = ft_calloc(sizeof(pthread_mutex_t) *
						master->input_info.philo_max);
	if (!master->mutexes.forks_lock)
		return (free_master(master), FAILURE);
	master->last_eat_us = ft_calloc(sizeof(t_time_us) *
						master->input_info.philo_max);
	if (!master->last_eat_us)
		return (free_master(master), FAILURE);
	return (SUCCESS);
}

void	free_master(t_master *master)
{
	if (master->philo_threads)
		free(master->philo_threads);
	if (master->grim_reaper_thread)
		free(master->grim_reaper_thread);
	if (master->philos_info)
		free(master->philos_info);
	if (master->mutexes.forks_lock)
		free(master->mutexes.forks_lock);
	if (master->last_eat_us)
		free(master->last_eat_us);
}
