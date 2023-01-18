/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:48:10 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/17 22:43:54 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	threading(t_table *table)
{
	size_t	i;

	i = 0;
	table->time_begin = get_time();
	while (i < table->philos_nb)
	{
		table->n_thread = i;
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				(void *)table))
			return (false);
		i++;
	}
	if (pthread_create(&table->maestro, NULL, &maestro_routine, (void *)table))
		return (false);
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
		if (table->philos[i].times_ate == 0)
		{
			if (pthread_detach(table->philos[i].thread))
				return (false);
		}
		else if (table->philos[i].times_ate)
		{
			if (pthread_join(table->philos[i].thread, NULL))
				return (false);
		}
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
