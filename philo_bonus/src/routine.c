/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:55:13 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/11 16:46:23 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

size_t	*routine(t_table *table, size_t i)
{
	if (table->repeat_time)
	{
		while (table->philos[i].times_ate && !table->is_philos_dead && i < table->philos_nb)
			{
				run_routine(table, i);
				printf("i %zu\n", i);
				i++;
			}
	}
	else
	{
		while (!table->is_philos_dead)
		{
			if (!run_routine(table, i))
				break ;
		}
	}
	return (NULL);
}

size_t	run_routine(t_table *table, size_t i)
{
	if (!eat(table, i))
		return (false);
	if (table->philos[i].times_ate)
	{
		if (!go_to_sleep(table, i))
			return (false);
		if (!think(table, i))
			return (false);
	}
	return (true);
}
