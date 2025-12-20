/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_training.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:24:40 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/20 19:37:41 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void	*thread_func(void *param)
{
	int	threadnum = *(int *)(param);

	printf("This is %d th thread\n", threadnum);
	return (0);
}

int	main(void)
{
	pthread_t	*threads;
	int			n;
	int			*nlst;

	n = 10;
	nlst = (int *)malloc(sizeof(int) * n);
	if (!nlst)
		return (1);
	for (int i = 0; i < n; i++)
	{
		nlst[i] = i;
	}
	threads = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (1);
	for (int i = 0; i < n; i++)
	{
		pthread_create(&(threads[i]), NULL, thread_func, &nlst[i]);
	}
	for (int i = 0; i < n; i++)
		pthread_join(threads[i], NULL);
	return (0);
}