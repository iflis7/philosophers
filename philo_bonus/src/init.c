/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:00:49 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/11 15:07:17 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static bool	manage_one_philo(t_table *table)
{
	time_t	present;

	present = 0;
	table->time_begin = get_time();
	sem_wait(&table->philos[0].chops.left);
	printf("%s%-10ld %-3zu %-30s%s\n", BBLUE, present, table->philos[0].id,
			CHOPSTICK1, RESET);
	create_delay(table->ultimatum);
	present = time_range(table->time_begin);
	printf("%s%-10ld %-3zu %-30s%s\n", BRED, present, table->philos[0].id, DEAD,
			RESET);
	sem_post(&table->philos[0].chops.left);
	table->is_philos_dead = true;
	return (false);
}

static bool	init_chops(t_table *table)
{
	size_t	i;

	// table->philos->chops = *(t_chopstick)malloc(sizeof(t_chopstick) * table->philos_nb);
	// if (table->philos->chops == NULL)
	// 	return (msg_error(ERRMAL));
	
	i = 0;
	while (i < table->philos_nb)
	{
		sem_open(table->philos[i].chops.s_left, O_CREAT, 0644, 0);
		sem_open(table->philos[i].chops.s_right, O_CREAT, 0644, 0);
		// if (pthread_mutex_init(&table->chopsticks[i], NULL) != 0)
			// return (false);
		i++;
	}
	return (true);
}

static bool	init_philos(t_table **table)
{
	size_t	i;
	size_t	j;

	(*table)->philos = malloc(sizeof(t_philos) * ((*table)->philos_nb + 1));
	if (!(*table)->philos)
		return (msg_error(ERRMAL));
	i = 0;
	j = 1;
	if (!init_chops(*table))
		return (msg_error(ERRMAL));
	while (i < (*table)->philos_nb)
	{
		(*table)->philos[i].id = i + 1;
		(*table)->philos[i].times_ate = (*table)->repeat_time;
		(*table)->philos[i].chops.left = i;
		if (i == (*table)->philos_nb - 1)
			(*table)->philos[i].chops.right = 0;
		else
			(*table)->philos[i].chops.right = j++;
		i++;
	}
	return (true);
}

bool	init_table(size_t argc, char **argv, t_table *table)
{
	table->philos_nb = ft_atol(argv[1]);
	table->ultimatum = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->repeat_time = ft_atol(argv[5]);
	if (!print_args_errors(table, argc))
		return (false);
	if (!init_philos(&table))
		return (false);
	table->is_philos_dead = false;
	if (table->philos_nb == 1)
		manage_one_philo(table);
	return (true);
}
