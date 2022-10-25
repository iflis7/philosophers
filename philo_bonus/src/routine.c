/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:55:13 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/21 10:42:45 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*death_reaper(void *args)
{
	t_philos	*philo;
	t_table		*table;

	philo = (t_philos *)args;
	table = philo->table;
	while (1)
	{
		if ((get_time() - philo->last_meal) > table->ultimatum
			&& philo->times_ate)
		{
			sem_wait(table->writing);
			printf("%s%-10ld %-3zu %-30s%s\n", BRED,
				time_range(table->time_begin), philo->id, DEAD, RESET);
			exit(1);
		}
		if ((get_time() - philo->last_meal) > table->ultimatum
			&& !philo->times_ate)
		{
			sem_wait(table->writing);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

bool	launch_simulation(t_table *table, size_t i)
{
	t_philos	philo;

	init_philos(table, &philo, i);
	pthread_create(&philo.death_reaper, NULL, death_reaper, &philo);
	while (1)
	{
		if (--philo.times_ate != 0)
		{
			eat(table, &philo);
			if (philo.times_ate != 1)
			{
				print_output(table, philo.id, BMAG, SLEEPING);
				create_delay(table->time_to_sleep);
				print_output(table, philo.id, BYEL, THINKING);
			}
		}
		else
			break ;
	}
	pthread_join(philo.death_reaper, NULL);
	return (true);
}
