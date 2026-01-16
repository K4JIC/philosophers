#include "philo.h"
#include <stdio.h>

static int	process_is_finished(t_philo_thread_info *philo_info)
{
	int	ret;

	pthread_mutex_lock(philo_info->flag_lock);
	ret = *philo_info->dead_philo_name;
	pthread_mutex_unlock(philo_info->flag_lock);
	if (ret != -1)
		return (1);
	return (0);
}

static int	is_full(t_philo_thread_info *philo_info)
{
	if (!philo_info->must_eat_option)
		return (0);
	if (philo_info->eat_count >= philo_info->must_eat)
	{
		// philo_write(philo_info, "is_full() fail");
		return (1);
	}
	return (0);
}

int	is_finished(t_philo_thread_info *philo_info)
{
	if (process_is_finished(philo_info))
		return (FAILURE);
	return (SUCCESS);
}
