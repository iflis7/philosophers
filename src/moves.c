#include "../include/philo.h"

t_bool	eat(t_master *master, size_t i)
{
	// if (is_philo_dead_func(master, &i))
	// 	return (False);
	// if (master->is_philo_dead)
	// 	return (False);
	if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.left]) != 0)
		return (False);
	if (!print_output(master, master->philos[i].id, BBLUE, CHOPSTICK1))
		return (False);
	if (pthread_mutex_lock(&master->chopsticks[master->philos[i].chops.right]) != 0)
		return (False);
	if (!print_output(master, master->philos[i].id, BBLUE, CHOPSTICK2))
		return (False);
	if (!print_output(master, master->philos[i].id, BGREEN, EATING))
		return (False);
	// pthread_mutex_lock(&master->writing_lock);
	master->philos[i].last_eat = get_time();
	// pthread_mutex_unlock(&master->writing_lock);
	make_one_sleep(master, master->time_to_eat, i);
	drop_chops(master, i);
	// if (is_philo_dead_func(master, &i))
	// 	return(False);
	return (True);
}

t_bool	make_one_sleep(t_master *master, time_t time, size_t i)
{
	time_t	get_up;

	if (is_philo_dead_func(master, &i))
		return (False);
	get_up = get_time() + time;
	while (get_time() < get_up)
	{
		if (is_philo_dead_func(master, &i))
			return (False);
	}
	// usleep(50);
	return (True);
}

t_bool	go_sleep(t_master *master, time_t time, size_t i)
{
	time_t	get_up;

	if (is_philo_dead_func(master, &i))
		return (False);
	if (master->is_philo_dead == True) 
		return (False);	
	get_up = get_time() + time;
	while (get_time() < get_up)
	{
		if (is_philo_dead_func(master, &i))
			return (False);
	}
	printf("DEAD OR NOT: %zu \n", master->is_philo_dead);
	if (master->is_philo_dead == True)
		return (False);
	if (!print_output(master, master->philos[i].id, BYEL, SLEEPING1))
		return (False);
	usleep(50);
	return (True);
}

t_bool	think(t_master *master, size_t prime, size_t i)
{
	time_t	thinking_time;

	if (is_philo_dead_func(master, &i))
		return (False);
	thinking_time = (master->ultimatum - (get_time()
				- master->philos[i].last_eat) - master->time_to_eat) / 2;
	if (thinking_time < 0)
		thinking_time = 0;
	if (prime && thinking_time == 0)
		thinking_time = 1;
	if (thinking_time > 600)
		thinking_time = 200;
	if (!master->is_philo_dead)
		return (False);
	if (prime)
		if (!print_output(master, master->philos[i].id, BMAG, THINKING))
			return (False);
	make_one_sleep(master, thinking_time, i);
	return (True);
}

t_bool	is_philo_dead_func(t_master *master, size_t *i)
{
	time_t	time;
	time_t	present;

	if (*i == master->philo_nb)
		*i = 0;
	// pthread_mutex_lock(&master->writing_lock);
	time = time_range(master->philos[*i].last_eat);
	// printf("time!! %zu \n", time);
	// printf("master->philos[*i].time_to_die!! %zu \n",
			// master->philos[*i].last_eat);
	// printf("master->ultimatum!! %zu \n", master->ultimatum);
	// printf("IN -- IN -- SHIT!! \n");
	if (time > master->ultimatum)
	{
		// printf("IN -- IN -- SHIT!! \n");
		// death_notice(master, *i);
		present = time_range(master->time_begin);
		// printf("IN present!! %zu \n", present);
		pthread_mutex_lock(&master->philos[*i].death_lock);
		master->is_philo_dead = True;
		pthread_mutex_unlock(&master->philos[*i].death_lock);
		printf("%s%-10ld %-3zu %-30s%s\n", BRED, present, master->philos[*i].id,
				DEAD, RESET);
		exit(0);
		// if (!print_output(master, master->philos[*i].id, BRED, DEAD))
		// {
		// pthread_mutex_unlock(&master->writing_lock);
		// }
		return (True);
	}
	i++;
	// pthread_mutex_unlock(&master->writing_lock);
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
