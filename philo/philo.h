/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:27:27 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/23 19:30:57 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>

# define SUCCESS 0
# define FAIL 1

typedef struct s_input_info
{
	int	philosophers_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	philosophers_must_eat;
}	t_input_info;

typedef struct s_thread_info
{
	int				thread_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	tty;
}	t_thread_info;

/*convert_input.h*/
int	convert_input(int argc, char **argv, t_input_info *input);

#endif
