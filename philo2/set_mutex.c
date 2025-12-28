/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:29:21 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/28 21:15:10 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * pthread_mutex_init() always returns 0
 */

void	set_mutexes(t_mutexes *mutexes, int philo_max)
{
	int	i;

	pthread_mutex_init(&mutexes->write_lock, NULL);
	pthread_mutex_init(&mutexes->death_lock, NULL);
	i = 0;
	while (i < philo_max)
	{
		pthread_mutex_init(&mutexes->forks_lock[i], NULL);
		i++;
	}
}

void	destroy_mutexes(t_mutexes *mutexes, int philo_max)
{
	int	i;

	pthread_mutex_destroy(&mutexes->write_lock);
	pthread_mutex_destroy(&mutexes->death_lock);
	i = 0;
	while (i < philo_max)
	{
		pthread_mutex_destroy(&mutexes->forks_lock[i]);
		i++;
	}
}
