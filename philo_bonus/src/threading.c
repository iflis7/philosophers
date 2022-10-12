/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:48:10 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/11 16:40:26 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	threading(t_table *table)
{
	size_t	i;

	i = 0;
	table->time_begin = get_time();
	sem_open(table->writing, O_CREAT, 0644, 0);
	while (i < table->philos_nb)
	{
		table->n_process = i;
		table->philos[i].pid = fork();
		printf("i %zu", i);
		if (table->philos[i].pid != 0 )
			printf("i %zu", i);
			
			
		if(table->philos[i].pid == 0)
			routine(table, i);
		waitpid(table->philos[i].pid, 0, 0);
		// if (pthread_create(&table->philos[i].pid, NULL, &routine,
		// 		(void *)table))
		// 	return (false);
		// printf("i %zu, table->philos[i].pid %d\n", i, table->philos[i].pid);
		i++;
	}
	return (true);
}
