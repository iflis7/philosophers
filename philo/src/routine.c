/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:55:13 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/19 16:02:17 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief The routine each philo should run
 * 
 * @param args The address of the struct to use 
 * @return void* 
 */
void	*routine(void *args)
{
	t_table	*table;
	size_t	i;

	table = (t_table *)args;
	i = table->n_thread;
	while (!table->is_philos_dead)
	{
		if (!eat(table, i))
			{drop_chops(table, i);
			return (false);}
		if (!go_to_sleep(table, i))
			return (false);
		if (!think(table, i))
			return (false);
	}
	return (NULL);
}

/**

	* @brief The routine the maestro should run to check if any other philo is dead or should die!
 * 
 * @param args The address of the struct to use 
 * @return void* 
 */
void	*maestro_routine(void *args)
{
	t_table	*table;
	size_t	i;

	table = (t_table *)args;
	i = 0;
	while (!table->is_philos_dead)
	{
		if (!table->philos[i].times_ate || is_philo_dead(table, i))
			break ;
	}
	return (NULL);
}
