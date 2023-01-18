/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:38 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/18 12:29:19 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Takes chops one after the other and taking the time needed to eat then dropping the chops
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if all well
 * @return false incase of an error
 */
bool	eat(t_table *table, size_t i)
{
	if (table->is_philos_dead)
		return (false);
	if (pthread_mutex_lock(&table->chopsticks[table->philos[i].chops.left]))
		return (false);
	if (!print_output(table, table->philos[i].id, BBLUE, CHOPSTICK1))
		return (false);
	if (pthread_mutex_lock(&table->chopsticks[table->philos[i].chops.right]))
		return (false);
	if (!print_output(table, table->philos[i].id, BBLUE, CHOPSTICK2))
		return (false);
	if (!print_output(table, table->philos[i].id, BGREEN, EATING))
		return (false);
	table->philos[i].time_to_die = get_time();
	create_delay(table->time_to_eat);
	drop_chops(table, i);
	return (true);
}

/**
 * @brief Put the philosopher to sleep.
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if all well
 * @return false if any error
 */
bool	go_to_sleep(t_table *table, size_t i)
{
	if (!print_output(table, table->philos[i].id, BYEL, SLEEPING))
		return (false);
	create_delay(table->time_to_sleep);
	return (true);
}

/**
 * @brief Thinking for a philo. Print it.
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if all well
 * @return false if any error
 */
bool	think(t_table *table, size_t i)
{
	time_t	akud;

	if (!table->is_philos_dead)
	{
		akud = time_range(table->time_begin);
		pthread_mutex_lock(&table->writing_lock);
		printf("%s%-10ld %-3zu %-30s%s\n", BMAG, akud, table->philos[i].id,
				THINKING, RESET);
		pthread_mutex_unlock(&table->writing_lock);
	}
	return (true);
}

/**
 * @brief Check if the philo is dead or not
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if the philo is dead
 * @return false if the philo is alive
 */
bool	is_philo_dead(t_table *table, size_t i)
{
	time_t	time;
	time_t	akud;

	akud = time_range(table->time_begin);
	time = time_range(table->philos[i].time_to_die);
	if (time > (time_t)table->ultimatum)
	{
		pthread_mutex_lock(&table->writing_lock);
		printf("%s%-10ld %-3zu %-30s%s\n", BRED, akud, table->philos[i].id,
				DEAD, RESET);
		table->is_philos_dead = true;
		pthread_mutex_unlock(&table->writing_lock);
		return (true);
	}
	return (false);
}

/**
 * @brief Drop the chops right and left
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if the philo is dead
 * @return false if the philo is alive
 */
bool	drop_chops(t_table *table, size_t i)
{
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.right]))
		return (false);
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.left]))
		return (false);
	table->philos[i].times_ate--;
	return (true);
}
