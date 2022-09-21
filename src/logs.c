#include "../include/philo.h"

void	msg_error(char *str)
{
	write(2, &(*str), ft_strlen(str));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
