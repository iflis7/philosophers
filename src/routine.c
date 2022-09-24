#include "../include/philo.h"

t_bool	execute_routine(t_master *master, size_t i)
{
	if (!eat(master, i))
		return (False);
	if (master->repeat_time > master->philos[i].times_ate)
	{
		if (!go_sleep(master, i))
			return (False);
		if (!think(master, i))
			return (False);
	}
	return (True);
}

void	*routine(void *args)
{
	t_master	*master;
	size_t		i;

	master = (t_master *)args;
	i = 0;
	pthread_mutex_lock(&master->writing_lock);
	i = master->thread_nb;
	pthread_mutex_unlock(&master->writing_lock);
	if (master->repeat_time)
	{
		while (master->philos[i].times_ate < master->repeat_time
			&& !master->is_philo_dead)
			execute_routine(master, i);
	}
	else
	{
		while (!master->is_philo_dead)
		{
			if (!execute_routine(master, i))
				break ;
		}
	}
	return (NULL);
}

void	*routine_maestro(void *args)
{
	t_master	*master;
	size_t		i;

	master = (t_master *)args;
	i = 0;
	if (master->repeat_time)
	{
		while (master->philos[i].times_ate < master->repeat_time
			&& !master->is_philo_dead)
			if (is_philo_dead(master, &i))
				break ;
	}
	else
	{
		while (!master->is_philo_dead)
		{
			if (!is_philo_dead(master, &i))
				break ;
		}
	}
	return (NULL);
}
