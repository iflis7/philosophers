#include "../include/philo.h"

int	main(int argc, char **argv)
{
    t_master *master;
	if (argc == 5 || argc == 6)
	{
		args_are_valid(argv);
        init_master(argc, argv, &master);
	}
	return(0);
}