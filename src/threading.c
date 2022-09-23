#include "../include/philo.h"



t_bool	eat(t_master *master, size_t i)
{
	if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.left]) != 0)
		return (False);
	if (print_output(master, master->philos[i].id, BBLUE, CHOPSTICK1) == False)
		return (False);
	// if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.right]) != 0)
	// 	return (False);
	// if (print_output(master, master->philos[i].id, BBLUE, CHOPSTICK2) == False)
	// 	return (False);
	// if (print_output(master, master->philos[i].id, BGREEN, EATING) == False)
	// 	return (False);
	// pthread_mutex_lock(&master->writing_lock);
	// master->philos[i].time_to_die = get_time();
	// pthread_mutex_unlock(&master->writing_lock);
	// time_excution(master->time_to_eat);
	// drop_forks(master, i);
    printf("Routine %zu ==> %zu\n", master->philos[i].id, i);
	return (True);
}


t_bool	execute_routine(t_master *master, size_t i)
{
	if (!eat(master, i))
		return (False);

	return (True);
}



void	*routine(void *args)
{
	t_master	*master;

	size_t		i;
	master = (t_master *)args;
    // return (NULL);

    i = master->thread_nb;
	if (master->repeat_time > master->philos[i].times_ate)
	{
		while (!master->is_philo_dead)
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
	printf("Routine %zu \n", master->philos->id);
    return(NULL);
}

t_bool	threading(t_master *master)
{
	size_t i;

	i = 0;
	master->time_begin = get_time();
	// if (pthread_mutex_init(&master->writing_lock, NULL) != 0)
	// 	return (False);
	while (i < master->philo_nb)
	{
		// pthread_mutex_lock(&master->writing_lock);
		// pthread_mutex_unlock(&master->writing_lock);
        master->thread_nb = i;
		if (pthread_create(&master->philos[i].thread, NULL, &routine,
				(void *)master) != 0)
			return (False);
		usleep(1000); // TODO recalculate the time
		i++;
	}
    if (join_threads(master) == False)
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
	return (True);
}