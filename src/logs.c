#include "../include/philo.h"

void	msg_error(char *str)
{
	write(2, &(*str), ft_strlen(str));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
void	print_help(char **argv)
{
	if (!ft_strncmp(argv[1], "help", 4) && ft_strlen(argv[1]) == 4)
	{
		printf("%s%s\n", BGREEN, HELP);
		exit(0);
	}
	msg_error(ERRHLP);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

time_t	delta_time(time_t time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}
