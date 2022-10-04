/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:48:10 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/04 19:23:14 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	threading(t_table *table)
{
	size_t	i;

	i = 0;
	table->time_begin = get_time();
	if (pthread_mutex_init(&table->writing_lock, NULL) != 0)
		return (false);
	while (i < table->philos_nb)
	{
		table->n_thread = i;
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				(void *)table))
			return (false);
		i++;
		usleep(1000);
	}
	if (pthread_create(&table->maestro, NULL, &maestro_routine, (void *)table))
		return (false);
	usleep(1000);
	if (!joining_threads(table))
		return (false);
	return (true);
}

bool	joining_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_nb)
	{
		// if (pthread_join(table->philos[i].thread, NULL))
		if (table->philos[i].times_ate == 0)
		{
			// printf("table->philos[%zu].times_ate %zu \n", i,	table->philos[i].times_ate);
			if (pthread_detach(table->philos[i].thread))
				return (false);
		}
		else if (table->philos[i].times_ate)
		{
			if (pthread_join(table->philos[i].thread, NULL))
				return (false);
		}
		// printf("Debug out! \n");
		i++;
	}
	if (pthread_join(table->maestro, NULL))
		return (false);
	return (true);
}

bool	destroying_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_nb)
	{
		pthread_mutex_destroy(&table->chopsticks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->writing_lock);
	return (true);
}
