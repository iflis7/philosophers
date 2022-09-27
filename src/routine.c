#include "../include/philo.h"

t_bool	execute_routine(t_master *master, size_t i)
{
	// if(is_philo_dead_func(master, &i))
	// 	return(False);
	// if(master->is_philo_dead)
	// 	return(False);
	if (!eat(master, i))
		return (False);
	go_sleep(master, master->time_to_sleep, i);
	// if(is_philo_dead_func(master, &i))
	// 	return(False);
	if(master->philos[i].id % 2)
		think(master, 1, i);
	think(master, 0, i);
	
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
	start_delay(master->time_begin);
	// pthread_mutex_lock(&master->death_lock);
	if (master->repeat_time)
	{
		while (master->philos[i].times_ate < master->repeat_time && !master->is_philo_dead)
			execute_routine(master, i);
	}
	else
	{
		// printf("WHAAAT!! \n");
					// pthread_mutex_lock(&master->philos[i].death_lock);
		while (!master->is_philo_dead)
		// while (!is_philo_dead_func(master, &i))
		{
			// printf("WHAAAT!!!!!! \n");
			if (!execute_routine(master, i))
				{					
			// pthread_mutex_unlock(&master->philos[i].death_lock);
				break ;
				}
				
			// pthread_mutex_unlock(&master->philos[i].death_lock);
		}
	}
	return (NULL);
}

// void	routine_maestro(t_master *master)
// {
// 	printf("WHAAAT!! \n");
// 	size_t		i;
// 	i = 0;
// 	if (master->repeat_time)
// 	{
// 		while ( master->philos[i].times_ate < master->repeat_time && !master->is_philo_dead)
// 			if (is_philo_dead_func(master, &i))
// 				break ;
// 	}
// 	else
// 	{
// 		// pthread_mutex_lock(&master->death_lock);
// 	while (master->is_philo_dead == False)
// 	{
// 		if (!is_philo_dead_func(master, &i))
// 			{
// 			// pthread_mutex_lock(&master->death_lock);
// 			break ;
// 			}
// 	}
// 	}
// }
