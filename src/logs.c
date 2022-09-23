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

	present = delta_time(master->time_begin);
	if (master->is_philo_dead)
		return (False);
	// pthread_mutex_unlock(&master->writing_lock);
	pthread_mutex_lock(&master->writing_lock);
	if (master->is_philo_dead)
	{
		pthread_mutex_unlock(&master->writing_lock);
		return (False);
	}
	else
		printf("%s%-10ld %-3zu %-30s%s\n", color, present, id, status, RESET);
	pthread_mutex_unlock(&master->writing_lock);
	return (True);
}
