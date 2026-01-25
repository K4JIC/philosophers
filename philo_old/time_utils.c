/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:56:26 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/13 20:56:29 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_time_us	convert_tv_to_ull(struct timeval tv)
{
	t_time_us	time_us;

	time_us = tv.tv_sec * SEC_TO_USEC + tv.tv_usec;
	return (time_us);
}

int	get_time_us(t_time_us *time_us)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (GET_TIME_ERROR);
	*time_us = convert_tv_to_ull(tv);
	return (SUCCESS);
}

int	get_time_duration_us(t_time_us *time_us,
						t_time_us start_clock_us)
{
	t_time_us	now_time_us;

	if (get_time_us(&now_time_us) == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	*time_us = now_time_us - start_clock_us;
	return (SUCCESS);
}
