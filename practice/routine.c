/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:13:04 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/27 17:23:08 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*philosophers_routine(void *param)
{
	t_thread_info	tinfo;

	tinfo = * (t_thread_info *)param;
	pthread_mutex_lock(&tinfo.tty);
	printf("This is %d thread.\n", tinfo.thread_num);
	pthread_mutex_unlock(&tinfo.tty);
}