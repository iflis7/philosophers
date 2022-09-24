#include "./include/philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("TIme: : %zu \n", time.tv_sec);
	printf("TIme1: %zu \n", (time.tv_sec * 1000));
	printf("TIme2: %d \n", (time.tv_usec / 1000));
	printf("TIme3: %zu \n", ((time.tv_sec * 1000) + (time.tv_usec / 1000)));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	time_range(time_t time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

int	main(void)
{
	printf("TIme: %zu \n", get_time());
	return (0);
}