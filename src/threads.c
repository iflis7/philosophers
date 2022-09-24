#include "../include/philo.h"
t_bool	threading(t_master *master)
{
	size_t	i;

	i = 0;
	master->time_begin = get_time();
	if (pthread_mutex_init(&master->writing_lock, NULL) != 0)
		return (False);
	while (i < master->philo_nb)
	{
		// pthread_mutex_lock(&master->writing_lock);
		master->thread_nb = i;
		// pthread_mutex_unlock(&master->writing_lock);
		if (pthread_create(&master->philos[i].thread, NULL, &shtick,
				(void *)master) != 0)
			return (False);
		usleep(1000); // TODO recalculate the time
		i++;
	}
	if (pthread_create(&master->maestro, NULL, &shtick_check,
			(void *)master) != 0)
		return (False);
	usleep(1000);
	if (!join_threads(master))
		return (False);
	return (True);
}

t_bool	join_threads(t_master *master)
{
	size_t	i;

	i = 0;
	while (i < master->philo_nb)
	{
		if (pthread_join(master->philos[i].thread, NULL) != 0)
			return (False);
		i++;
	}
	if (pthread_join(master->maestro, NULL) != 0)
		return (False);
	return (True);
}
