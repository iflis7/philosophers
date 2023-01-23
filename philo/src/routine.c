/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:55:13 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/23 16:31:52 by hsaadi           ###   ########.fr       */
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
	// i = table->n_thread;
	printf("Philo ID: %ld\n", table->philos->id);
	i =  table->philos->id - 1;
	
	while (!table->is_philos_dead)
	{
		if (!eat(table, i))
		{
			drop_chops(table, i);
			return (false);
		}
		if (!go_to_sleep(table, i))
			return (false);
		if (!think(table, i))
			return (false);
	}
	return (NULL);
}

bool	still_time_to_repeat(int *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] != 7)
			return (false);
		i++;
	}
	return (true);
}

// int *fill_up()
// {
// 	int *tab[200];
// 	int i = 0;	
// 	while(tab[i])
// 	{
// 		*tab[i] = 7;
// 		i++;
// 	}
// 	return (*tab);
// }

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
	// int *tab = fill_up();
	// memset(tab, 0, sizeof(tab));
	// int tab[0] = 0;
	// printf("Tab:: %d\n", tab[0]);
	table = (t_table *)args;
	i = 0;
	while (!table->is_philos_dead)
	{
		// pthread_mutex_lock(&table->writing_lock);
		// if (table->philos[i].times_ate == 0)
			// tab[i] = 1;
		// pthread_mutex_unlock(&table->writing_lock);
		// printf("table->philos_nb: %ld\n", table->philos_nb);
		// if (i == table->philos_nb - 1)
		// 	i = 0;
		// printf("i: %ld\n", i);
		// printf("Time: %ld\n", table->philos[i].times_ate);
		// if (still_time_to_repeat(tab) || is_philo_dead(table, i))
		// if (still_time_to_repeat(tab) || is_philo_dead(table, i))
		if (is_philo_dead(table, i))
			break ;
		i++;
	}
	return (NULL);
}
