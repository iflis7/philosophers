/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:26 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 01:42:39 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	msg_error(char *str)
{
	write(2, &(*str), ft_strlen(str));
	write(2, "\n", 1);
	return (false);
}

bool	print_output(t_table *table, size_t id, char *color, char *status)
{
	time_t	present;

	present = time_range(table->time_begin);
	pthread_mutex_lock(&table->writing_lock);
	if (table->is_philos_dead)
	{
		pthread_mutex_unlock(&table->writing_lock);
		return (false);
	}
	else
		printf("%s%-10ld %-3zu %-30s%s\n", color, present, id, status, RESET);
	pthread_mutex_unlock(&table->writing_lock);
	return (true);
}

void	philos_free(t_table *table)
{
	free(table->chopsticks);
	free(table->philos);
}

void	start_some_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}
