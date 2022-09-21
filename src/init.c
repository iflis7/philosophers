#include "../include/philo.h"

void	init_master(size_t argc, char **argv, t_master **master)
{
	(*master) = malloc(sizeof(t_master) * 1);
	if (!master)
		msg_error(ERRMAL);
	(*master)->philo_nb = ft_atol(argv[1]);
	(*master)->time_to_die = ft_atol(argv[2]);
	(*master)->time_to_eat = ft_atol(argv[3]);
	(*master)->time_to_sleep = ft_atol(argv[4]);
	// (*master)->repeat_time = 0; 
	if (argv[5])
		(*master)->repeat_time = ft_atol(argv[5]);
	print_args_errors(*master, argc);
}
