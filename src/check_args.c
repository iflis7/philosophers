#include "../include/philo.h"

void	args_are_valid(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				msg_error(ERRARG);
			j++;
		}
		i++;
	}
}

void	print_args_errors(t_master *master, size_t argc)
{
	if (!master->philo_nb || !master->time_to_die || !master->time_to_eat
		|| !master->time_to_sleep)
	{
		printf("%s%s\n", BRED, ERRARG);
		exit(0);
	}
	if (argc == 6 && !master->repeat_time)
	{
		printf("%s%s\n", BRED, ERRARG);
		exit(0);
	}
}

