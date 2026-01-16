/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_error_and_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 19:24:30 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/28 20:45:21 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_puterrmsg(char *errmsg)
{
	int	mlen;

	if (!errmsg)
		return (FAILURE);
	mlen = 0;
	while (errmsg[mlen])
		mlen++;
	if (write(2, errmsg, mlen) == -1)
		return (FAILURE);
	return (SUCCESS);
}

static int	raise_error_and_exit(t_master *master, char *errmsg)
{
	free_master(master);
	ft_puterrmsg(errmsg);
	return (1);
}

int	input_error(t_master *master)
{
	return (raise_error_and_exit(master, "Error : Forbidden input.\n"));
}

int	malloc_error(t_master *master)
{
	return (raise_error_and_exit(master, "Error : malloc() FAILUREed.\n"));
}

int	gettime_error(t_master *master)
{
	return (raise_error_and_exit(master, "Error : gettimeofday() FAILUREed.\n"));
}

int	threads_error(t_master *master)
{
	return (raise_error_and_exit(master, "Error : FAILUREed to launch threads.\n"));
}
