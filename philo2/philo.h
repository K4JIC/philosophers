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
# include <string.h>
# include <pthread.h>
# include <stdio.h>

# define SUCCESS 0
# define FAILURE 1
# define SEC_TO_USEC 1000000
# define INT_MAX_CHAR "2147483647"
# define INT_MIN_CHAR "-2147483648"

typedef unsigned long long t_time_us;

enum error_identifier
{
	GET_TIME_ERROR=-1,
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
	pthread_mutex_t	flag_lock;
}						t_mutexes;

typedef struct s_thread_info
{
	t_time_us			start_time_us;
	t_time_us			last_eat_us;
	t_time_us			unit_time_us;
	int					philo_num;
	int					philo_max;
	int					time_to_die_ms;
	int					time_to_eat_ms;
	int					time_to_sleep_ms;
	int					time_to_think_ms;
	pthread_mutex_t		*rfork_lock;
	pthread_mutex_t		*lfork_lock;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*flag_lock;
	int					*finish_flag;
	int					*Im_died;
	int					must_eat_option;
	int					must_eat;
	int					eat_count;
}						t_thread_info;

typedef struct s_grim_reaper_thread_info
{
	int			philo_max;
	t_time_us	start_time_us;
	t_time_us	time_to_die_us;
	t_time_us	term_time_us;
	t_time_us	*last_eat_us;
	int			dead_philo_name;
}				t_grim_reaper_thread_info;

typedef struct s_master
{
	t_input_info		iinfo;
	t_mutexes			mutexes;
	pthread_t			*threads;
	pthread_t			*observe_thread;
	t_time_us			term_time_us;
	t_thread_info		*threads_info;
	int					philo_must_eat;
	int					*someone_died;
	int					finish_flag;
	int					must_eat_option;
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

/*routine_finish.c*/
int	is_finished(t_thread_info *tinfo);

/*routine_action.c*/
int	philo_eat(t_thread_info *tinfo);
int	philo_sleep(t_thread_info *tinfo);
int	philo_think(t_thread_info *tinfo);

/*routine.c*/
void	*philo_routine(void *info);
void	*observe_routine(void *master_void);
int	philo_write(t_thread_info *tinfo, char *msg);// 後で消す

/*launch_threads.c*/
int		launch_threads(t_master *master);

/*raise_error.c*/
int	input_error(t_master *master);
int	malloc_error(t_master *master);
int	gettime_error(t_master *master);
int	threads_error(t_master *master);

/*time_utils.c */
int	get_time_us(t_time_us *time_us);
int	get_time_duration_us(t_time_us *time_us,
						t_time_us start_time_us);

#endif
