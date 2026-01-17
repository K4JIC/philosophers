/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:27:27 by tozaki            #+#    #+#             */
/*   Updated: 2025/12/27 21:17:56 by tozaki           ###   ########.fr       */
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
	int	philo_max;
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
	int				time_to_think;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	tty;
}	t_thread_info;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	tty;
	pthread_mutex_t	death;
}	t_mutexes;

typedef struct s_philo
{
	t_input_info	iinfo;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	tty;
	pthread_mutex_t	death_lock;
	int				is_dead;
}	t_philo;

/*convert_input.c*/
int	convert_input(int argc, char **argv, t_input_info *input);

/*launch_threads.c*/
int	launch_threads(t_input_info iinfo, t_mutexes mutexes);

/*routine.c*/
void	*philosophers_routine(void *param);

#endif
