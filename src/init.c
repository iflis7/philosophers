#include "../include/philo.h"

void	init_chops(t_master *master)
{
	master->chopsticks = malloc(sizeof(pthread_mutex_t) * master->philo_nb);
	if (!master->chopsticks)
		msg_error(ERRMAL);
}

static void	find_best_chops(t_philo *philo)
{
	philo->chops.left = philo->id;
	philo->chops.right = (philo->id + 1) % philo->master.philo_nb;
	if (philo->id % 2)
	{
		philo->chops.left = (philo->id + 1) % philo->master.philo_nb;
		philo->chops.right = philo->id;
	}
}

t_philo	*init_philos(t_master **master)
{
	t_philo	**philos;
	size_t	i;

	philos = malloc(sizeof(t_philo) * ((*master)->philo_nb));
	if (!philos)
		msg_error(ERRMAL);
	i = 0;
	init_chops(*master);
	while (i < (*master)->philo_nb)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			msg_error(ERRMAL);
		philos[i]->master = *(*master);
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		find_best_chops(philos[i]);
		i++;
	}
	return (*philos);
}

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
