#include "../include/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_atol(const char *str)
{
	size_t	i;
	size_t	num;
	size_t	sign;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	time_range(time_t time)
{
	// printf("Time: %zu\n", ((time * 1000) + (time / 1000)));
	// printf("get_time(): %zu\n", get_time());
	// printf(" time: %zu\n", time);
	// printf("get_time() - time %zu\n", get_time() - time);
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	create_delay(time_t time)
{
	usleep(time * 100);
}

void	start_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}

// void death_notice(t_master *master, size_t i)
// {
// 	pthread_mutex_lock(&master->death_lock);
// 	master->is_philo_dead = True;
// 	pthread_mutex_unlock(&master->death_lock);
// 	print_output(master, master->philos[i].id, BRED, DEAD);
// }

// t_bool	philo_is_dead(t_master *master)
// {
// 	t_bool	status;

// 	status = false;
// 	pthread_mutex_lock(&master->death_lock);
// 	if (master->is_philo_dead == true)
// 		status = true;
// 	pthread_mutex_unlock(&master->death_lock);
// 	return (status);
// }