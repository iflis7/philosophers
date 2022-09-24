#include "../include/philo.h"

t_bool	eat(t_master *master, size_t i)
{
	if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.left]) != 0)
		return (False);
	if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.right]) != 0)
		return (False);
	if (!print_output(master, master->philos[i].id, BBLUE, CHOPSTICK2))
		return (False);
	if (!print_output(master, master->philos[i].id, BGREEN, EATING))
		return (False);
	// pthread_mutex_lock(&master->writing_lock);
	master->philos[i].time_to_die = get_time();
	// pthread_mutex_unlock(&master->writing_lock);
	create_delay(master->time_to_eat);
	// usleep(master->time_to_eat * 1000);
	drop_chops(master, i);
	return (True);
}

t_bool	go_sleep(t_master *master, size_t i)
{
	if (!print_output(master, master->philos[i].id, BYEL, SLEEPING))
		return (False);
	create_delay(master->time_to_eat);
	// usleep(master->time_to_eat * 1000);
	return (True);
}

t_bool	think(t_master *master, size_t i)
{
	if (!print_output(master, master->philos[i].id, BMAG, THINKING))
		return (False);
	// pthread_mutex_lock(&master->writing_lock);
	// usleep(master->time_to_eat * 1000);
	create_delay(master->time_to_eat);
	// pthread_mutex_unlock(&master->writing_lock);
	return (True);
}

t_bool	is_philo_dead(t_master *master, size_t *i)
{
	time_t	time;

	if (*i == master->philo_nb)
		*i = 0;
	// pthread_mutex_lock(&master->writing_lock);
	time = time_range(master->philos[*i].time_to_die);
	// pthread_mutex_unlock(&master->writing_lock);
	if (time > master->philos[*i].time_to_die)
	{
		if (!print_output(master, master->philos[*i].id, BRED, DEAD))
			master->is_philo_dead = True;
		return (True);
	}
	i++;
	return (False);
}

t_bool	drop_chops(t_master *master, int i)
{
	if (pthread_mutex_unlock(&master->chopsticks[master->philos[i].chops.left]))
		return (False);
	if (pthread_mutex_unlock(&master->chopsticks[master->philos[i].chops.right]))
		return (False);
	// pthread_mutex_lock(&master->writing_lock);
	master->philos[i].times_ate++;
	// pthread_mutex_unlock(&master->writing_lock);
	return (True);
}
