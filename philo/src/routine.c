/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:55:13 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/18 12:59:04 by hsaadi           ###   ########.fr       */
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
	if (table->repeat_time)
	{
		while (table->philos[i].times_ate && !table->is_philos_dead)
			run_routine(table, i);
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

/**
 * @brief Run the enire routine, eat, sleep and think 
 * 
 * @param table The table struct 
 * @param i The philo index
 * @return size_t return True if ll well or false if somthing went wrong!
 */
size_t	run_routine(t_table *table, size_t i)
{
	if (!table->is_philos_dead && !eat(table, i))
		return (false);
	if (!go_to_sleep(table, i))
		return (false);
	if (!think(table, i))
		return (false);
	return (true);
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
	if (table->philos[i].times_ate)
	{
		while (table->philos[i].times_ate && !table->is_philos_dead)
		{
			if (is_philo_dead(table, i))
				break ;
		}
	}
	else
	{
		while (!table->is_philos_dead)
		{
			if (is_philo_dead(table, i))
				break ;
		}
	}
	return (NULL);
}
