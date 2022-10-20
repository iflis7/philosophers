/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:55:13 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 02:38:49 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*death_reaper(void *args)
{
	t_philos	*philo;
	t_table		*table;

	philo = (t_philos *)args;
	table = philo->table;
	while (philo->times_ate)
	{
		if (time_range(philo->time_to_die) > table->ultimatum
			&& philo->times_ate )
		{
			// print_output(table, philo->id, BRED, DEAD);
			printf("%s%-10ld %-3zu %-30s%s\n", BRED, time_range(table->time_begin), philo->id, DEAD, RESET);
			// kill(table->philos->pid, SIGINT);
			exit(-1);
			return (NULL);

		}
		if (time_range(philo->time_to_die) > table->ultimatum
			&& !philo->times_ate)
			exit(1);
		usleep(1000);
	}
	return (NULL);
}

void	init_philo(t_table *table, t_philos *philos, int i)
{
	philos->id = i + 1;
	philos->times_ate = table->repeat_time;
	philos->time_to_die = table->time_begin;
	philos->table = table;
}

void	launch_simulation(t_table *table, int i)
{
	t_philos	philo;
	init_philo(table, &philo, i);
	pthread_create(&philo.death_reaper, NULL, death_reaper, &philo);
	while (true)
	{
		if (--philo.times_ate)
		{
			ft_eating(table, &philo);
			if (philo.times_ate != 1)
			{
				print_output(table, philo.id, BYEL, SLEEPING);
				create_delay(table->time_to_sleep);
				print_output(table, philo.id, BMAG, THINKING);
			}
		}
		else
			break ;
	}
	pthread_join(philo.death_reaper, NULL);
	// pthread_detach(philo.death_reaper);
	exit(0);
}
