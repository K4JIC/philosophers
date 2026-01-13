/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:54:47 by tozaki            #+#    #+#             */
/*   Updated: 2026/01/11 16:56:17 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define SEC_TO_USEC 1000000

enum error_identifier
{
	GETTIMEERROR,
	INPUTERROR,
	MALLOCERROR
};

typedef struct s_input_info
{
	int	philo_max;
	int	time_to_die_ms;
	int	time_to_eat_ms;
	int	time_to_sleep_ms;
	int	philo_must_eat;
}		t_input_info;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
}						t_mutexes;

typedef struct s_thread_info
{
	unsigned long long	start_time_us;
	unsigned long long	last_eat_us;
	int					philo_num;
	int					philo_max;
	int					time_to_die_ms;
	int					time_to_eat_ms;
	int					time_to_sleep_ms;
	int					time_to_think_ms;
	pthread_mutex_t		*rfork_lock;
	pthread_mutex_t		*lfork_lock;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*death_lock;
	int					*Im_died;
}						t_thread_info;

typedef struct s_master
{
	t_input_info		iinfo;
	t_mutexes			mutexes;
	pthread_t			*threads;
	pthread_t			*observe_thread;
	unsigned long long	term_time_us;
	t_thread_info		*threads_info;
	int					philo_must_eat;
	int					*someone_died;
}					t_master;

/*set_argv.c*/
int		set_argv(int argc, char **argv, t_input_info *iinfo);

/*set_malloc.c*/
int		set_malloc(t_master *master);
void	free_master(t_master *master);

/*set_mutex.c*/
void	set_mutexes(t_mutexes *mutex, int philo_max);
void	destroy_mutexes(t_mutexes *mutex, int philo_max);

/*set_thread_info.c*/
int		set_threads_info(t_master *master);

/*routine.c*/
void	*philo_routine(void *info);
void	*observe_routine(void *master_void);

/*launch_threads.c*/
int		launch_threads(t_master *master);

/*raise_error.c*/
int	input_error(t_master *master);
int	malloc_error(t_master *master);
int	gettime_error(t_master *master);
int	threads_error(t_master *master);

/*time_utils.c */
int	get_time_us(unsigned long long *time_us);
int	get_time_duration_us(unsigned long long *time_us,
						unsigned long long start_time_us);

#endif
