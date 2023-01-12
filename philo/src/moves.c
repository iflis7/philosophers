/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:38 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/12 18:30:50 by hsaadi           ###   ########.fr       */
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
	if (!print_output(table, table->philos[i].id, BMAG, THINKING))
		return (false);
	return (true);
}

bool	is_philo_dead(t_table *table, size_t *i)
{
	size_t	time;

	time = time_range(table->philos[*i].time_to_die);
	if (time > table->ultimatum)
	{
		pthread_mutex_lock(&table->writing_lock);
		printf("%s%-10ld %-3zu %-30s%s\n", BRED, time, table->philos[*i].id, DEAD, RESET);
		table->is_philos_dead = true;
		pthread_mutex_unlock(&table->writing_lock);
		return (true);
	}
	return (false);
}

bool	drop_chops(t_table *table, size_t i)
{
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.left]))
		return (false);
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.right]))
		return (false);
	table->philos[i].times_ate--;
	return (true);
}
