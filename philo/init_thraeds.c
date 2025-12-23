/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thraeds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:26:24 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/23 19:42:36 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * given t_input_info
 * define t_thread_info
 * set routine function
 */

#include "philo.h"
#include <stdlib.h>

void	*philosophers_routine(void *param)
{
	t_thread_info	info;

	info = * (t_thread_info *)param;
}

t_thread_info	*pack_thread_info(t_input_info input_info,
								pthread_mutex_t right_fork,
								pthread_mutex_t left_fork,
								pthread_mutex_t tty)
{
	t_thread_info	*thread_info;

	thread_info = (t_thread_info *)malloc(sizeof(t_thread_info));
	if (!thread_info)
		return (NULL);
	thread_info->time_to_die = input_info.time_to_die;
	thread_info->time_to_eat = input_info.time_to_eat;
	thread_info->time_to_sleep = input_info.time_to_sleep;
	thread_info->right_fork = right_fork;
	thread_info->left_fork = left_fork;
	thread_info->tty = tty;
	return (thread_info);
}

t_thread_info	*convert_input_info(t_input_info input_info);


int	init_one_thread(pthread_t thread, t_thread_info thread_info, int thread_num)
{
	if (pthread_create(thread, NULL, philosophers_routine, &thread_info))
		return (FAIL);
	return (SUCCESS);
}

int	init_threads(t_input_info t_input_info)
{
	
}