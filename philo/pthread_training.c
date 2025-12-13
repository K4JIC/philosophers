/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_training.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:24:40 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/13 17:39:35 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

void	*thread_fun

int	main(void)
{
	pthread_t	thread;
	int	ret = 0;

	ret = pthread_create(&thread, NULL, thread_func, NULL);
}