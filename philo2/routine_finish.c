#include "philo.h"
#include <stdio.h>

static int	process_is_finished(t_thread_info *tinfo)
{
	int	ret;

	pthread_mutex_lock(tinfo->flag_lock);
	ret = *tinfo->finish_flag;
	pthread_mutex_unlock(tinfo->flag_lock);
	if (ret == 1)
		return (1);
	return (0);
}

static int	is_alive(t_thread_info *tinfo)
{
	unsigned long long	hungry_time_us;

	if (get_time_duration_us(&hungry_time_us, tinfo->last_eat_us))
		return (GET_TIME_ERROR);
	if (hungry_time_us / 1000 > (unsigned long long)tinfo->time_to_die_ms)
	{
		printf("%d ", tinfo->philo_num);
		printf("hungry = %lld\n", hungry_time_us);
		printf("%d ", tinfo->philo_num);
		printf("last_eat = %lld\n", tinfo->last_eat_us);
		philo_write(tinfo, "is_alive() fail");
		*tinfo->Im_died = 1;
		return (0);
	}
	return (1);
}

static int	is_full(t_thread_info *tinfo)
{
	if (!tinfo->must_eat_option)
		return (0);
	if (tinfo->eat_count >= tinfo->must_eat)
	{
		philo_write(tinfo, "is_full() fail");
		return (1);
	}
	return (0);
}

static int	thread_is_finished(t_thread_info *tinfo)
{
	int	isalive;

	isalive = is_alive(tinfo);
	if (isalive == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (is_full(tinfo) || !isalive)
	{
		philo_write(tinfo, "thread_is_finished() fail");
		pthread_mutex_lock(tinfo->flag_lock);
		*tinfo->finish_flag = 1;
		pthread_mutex_unlock(tinfo->flag_lock);
		return (1);
	}
	return (0);
}

int	is_finished(t_thread_info *tinfo)
{
	int	thisfinished;

	thisfinished = thread_is_finished(tinfo);
	if (thisfinished == GET_TIME_ERROR)
		return (GET_TIME_ERROR);
	if (thisfinished)
	{
		philo_write(tinfo, "is_finished() fail");
		return (FAILURE);
	}
	if (process_is_finished(tinfo))
		return (FAILURE);
	return (SUCCESS);
}
