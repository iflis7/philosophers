#include "../include/philo.h"

void	msg_error(char *str)
{
	write(2, &(*str), ft_strlen(str));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

t_bool	print_output(t_master *master, size_t id, char *color, char *status)
{
	time_t	present;

	// present = time_range(master->philos[id].master.time_begin);
	present = time_range(master->time_begin);
	// get_time_in_ms() - philo->table->start_time
	// if (master->is_philo_dead)
	// 	return (False);
	pthread_mutex_lock(&master->philos[id].death_lock);
	// if(is_philo_dead(master, &id))
	// 	return(False);

	// if (is_philo_dead_func(master, &id))
	// printf("DEAD OR NOT: %zu \n", master->is_philo_dead);
	if (master->is_philo_dead)
	{
		master->is_philo_dead = True;
		pthread_mutex_unlock(&master->philos[id].death_lock);
		return (False);
	}
	else
		printf("%s%-10ld %-3zu %-30s%s\n", color, present, id + 1, status, RESET);
	pthread_mutex_unlock(&master->philos[id].death_lock);
	return (True);
}
