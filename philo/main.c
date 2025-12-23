/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:35:50 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/23 15:30:06 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philostatus(char *);

int	argument_error(void)
{
	write(1, "Error : Wrong arguments\n", 24);
	return (1);
}

int	main(int argc, char **argv)
{
	t_input_info	input;

	if (argc != 5 && argc != 6)
		return (argument_error());
	if (convert_input(argc, argv, &input) == FAIL)
		return (argument_error());
}