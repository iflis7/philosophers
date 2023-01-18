/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:38 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/17 22:42:52 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	eat(t_table *table, size_t i)
{
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

bool	go_to_sleep(t_table *table, size_t i)
{
	if (!print_output(table, table->philos[i].id, BYEL, SLEEPING))
		return (false);
	create_delay(table->time_to_sleep);
	return (true);
}

bool	think(t_table *table, size_t i)
{
	time_t	akud;

	akud = time_range(table->time_begin);
	pthread_mutex_lock(&table->writing_lock);
	printf("%s%-10ld %-3zu %-30s%s\n", BMAG, akud, table->philos[i].id,
			THINKING, RESET);
	pthread_mutex_unlock(&table->writing_lock);
	return (true);
}

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

bool	drop_chops(t_table *table, size_t i)
{
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.right]))
		return (false);
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.left]))
		return (false);
	table->philos[i].times_ate--;
	return (true);
}
