/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:27:14 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/23 15:28:18 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

static int	validate_atoi(int *integer, char *ascii)
{
	int	res;
	int	i;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(ascii[i]))
		i++;
	if (ascii[i] == '-' || ascii[i] == '+')
	{
		if (ascii[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isnum(ascii[i]))
		return (FAIL);
	while (ft_isnum(ascii[i]))
	{
		res = res * 10 + (ascii[i] - '0');
		i++;
	}
	*integer = res * sign;
	return (SUCCESS);
}

int	convert_input(int argc, char **argv, t_input_info *input)
{
	if (validate_atoi(&(input->philosophers_count), argv[1]) == FAIL)
		return (FAIL);
	if (validate_atoi(&(input->time_to_die), argv[2]) == FAIL)
		return (FAIL);
	if (validate_atoi(&(input->time_to_eat), argv[3]) == FAIL)
		return (FAIL);
	if (validate_atoi(&(input->time_to_sleep), argv[4]) == FAIL)
		return (FAIL);
	if (argc == 6)
	{
		if (validate_atoi(&(input->philosophers_must_eat), argv[5]) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}