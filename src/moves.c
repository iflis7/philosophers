#include "../include/philo.h"

t_bool	philo_eat(t_master *master, size_t i)
{
	if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.left]) != 0)
		return (False);
	if (print_output(master, master->philos[i].id, BBLUE, CHOPSTICK1) == False)
		return (False);
	if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.right]) != 0)
		return (False);
	if (print_output(master, master->philos[i].id, BBLUE, CHOPSTICK2) == False)
		return (False);
	if (print_output(master, master->philos[i].id, BGREEN, EATING) == False)
		return (False);
	pthread_mutex_lock(&master->writing_lock);
	master->philos[i].time_to_die = get_time();
	pthread_mutex_unlock(&master->writing_lock);
	time_excution(master->time_to_eat);
	drop_forks(master, i);
	return (True);
}

t_bool	drop_forks(t_master *master, size_t i)
{
	if (pthread_mutex_unlock(&master->chopsticks[master->philos[i].chops.left]))
		return (False);
	if (pthread_mutex_unlock(&master->chopsticks[master->philos[i].chops.right]))
		return (False);
	master->philos[i].times_ate++;
	return (True);
}

t_bool	philo_is_dead(t_master *master, size_t *i)
{
	int	time;

	if (*i == master->philo_nb)
		*i = 0;
	time = delta_time(master->philos[*i].time_to_die);
	if (time > master->time_to_die)
	{
		print_output(master, master->philos[*i].id, BMAG, DEAD);
		pthread_mutex_lock(&master->writing_lock);
		master->is_philo_dead = True;
		pthread_mutex_unlock(&master->writing_lock);
		return (True);
	}
	i++;
	return (False);
}
