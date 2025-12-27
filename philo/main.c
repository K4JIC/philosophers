/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:35:50 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/27 17:24:48 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philostatus(char *);

int	argument_error(void)
{
	write(1, "Error : Wrong arguments.\n", 25);
	return (1);
}

int	malloc_error(void)
{
	write(1, "Error : Malloc failed.\n", 23);
	return (1);
}

int	launch_error(void)
{
	write(1, "Error : An error occured while launch threads.\n", 47);
	return (1);
}

void	free_all(t_mutexes s_mutexes, )

int	main(int argc, char **argv)
{
	t_input_info	iinfo;
	t_mutexes		mutexes;

	if (argc != 5 && argc != 6)
		return (argument_error());
	if (convert_input(argc, argv, &iinfo) == FAIL)
		return (argument_error());
	mutexes.forks = fork_init(iinfo);
	if (!mutexes.forks)
		return (malloc_error());
	if (launch_threads(iinfo, mutexes) == FAIL)
		return (launch_error());
}