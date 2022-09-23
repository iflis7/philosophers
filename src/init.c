#include "../include/philo.h"

t_bool	init_chops(t_master *master)
{
	size_t	i;

	master->chopsticks = malloc(sizeof(pthread_mutex_t) * master->philo_nb);
	if (master->chopsticks == NULL)
		msg_error(ERRMAL);
	i = 0;
	while (i < master->philo_nb)
	{
		if (pthread_mutex_init(&master->chopsticks[i], NULL) != 0)
			return (False);
		i++;
	}
	return (True);
}

static void	find_best_chops(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->chops.left = (philo->id + 1) % philo->master.philo_nb;
		philo->chops.right = philo->id;
	}
	else
	{
		philo->chops.left = philo->id;
		philo->chops.right = (philo->id + 1) % philo->master.philo_nb;
	}
}

void	init_philos(t_master **master)
{
	size_t	i;

	(*master)->philos = malloc(sizeof(t_philo) * ((*master)->philo_nb));
	if (!(*master)->philos)
		msg_error(ERRMAL);
	i = 0;
	if (init_chops(*master) == False)
		msg_error(ERRMAL);
	while (i < (*master)->philo_nb)
	{
		(*master)->philos[i].master = *(*master);
		(*master)->philos[i].id = i;
		(*master)->philos[i].times_ate = 0;
		find_best_chops(&(*master)->philos[i]);
		i++;
	}
}

void	init_master(size_t argc, char **argv, t_master **master)
{
	(*master) = malloc(sizeof(t_master) * 1);
	if (!master)
		msg_error(ERRMAL);
	(*master)->philo_nb = ft_atol(argv[1]);
	(*master)->ultimatum = ft_atol(argv[2]);
	(*master)->time_to_eat = ft_atol(argv[3]);
	(*master)->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		(*master)->repeat_time = ft_atol(argv[5]);
	print_args_errors(*master, argc);
	init_philos(master);
	(*master)->is_philo_dead = False;
}
