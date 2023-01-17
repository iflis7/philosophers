/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:00:49 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/17 15:30:58 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	manage_one_philo(t_table *table)
{
	time_t	present;

	present = 0;
	table->time_begin = get_time();
	pthread_mutex_lock(&table->chopsticks[table->philos[0].chops.left]);
	printf("%s%-10ld %-3zu %-30s%s\n", BBLUE, present, table->philos[0].id,
		CHOPSTICK1, RESET);
	create_delay(table->ultimatum);
	present = time_range(table->time_begin);
	printf("%s%-10ld %-3zu %-30s%s\n", BRED, present, table->philos[0].id, DEAD,
		RESET);
	pthread_mutex_unlock(&table->chopsticks[table->philos[0].chops.left]);
	table->is_philos_dead = true;
	return (false);
}

static bool	init_chops(t_table *table)
{
	size_t	i;

	table->chopsticks = malloc(sizeof(pthread_mutex_t) * table->philos_nb);
	if (table->chopsticks == NULL)
		return (msg_error(ERRMAL));
	i = 0;
	while (i < table->philos_nb)
	{
		if (pthread_mutex_init(&table->chopsticks[i], NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_mutex_init(&table->writing_lock, NULL) != 0)
		return (false);
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
	if(ft_atol(argv[1]) > 200)
		table->philos_nb = 200;
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
