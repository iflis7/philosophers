/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:48:10 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 02:26:27 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	creating_pids(t_table *table)
{
	size_t	i;

	i = -1;
	table->pids = (pid_t *)(malloc(sizeof(pid_t) * table->philos_nb));
	if (!table->pids)
		return (false);
	table->time_begin = get_time() + (table->philos_nb * 2 * 10);
	while (++i < table->philos_nb)
	{
		table->pids[i] = fork();
		if (table->pids[i] == -1)
			return (false);
		else if (table->pids[i] == 0)
		{
			start_some_delay(table->time_begin);
			launch_simulation(table, i);
		}
		usleep(100);
	}
	waiting(table);
	return (true);
}

void	waiting(t_table *table)
{
	size_t i;
	int status;

	i = -1;
	while (++i < table->philos_nb)
	{
		waitpid(table->philos->pid, &status, 0);
		if (status)
		{
			ft_kill_pids(table);
			break ;
		}
	}
	sem_close(table->chops);
	sem_close(table->writing_lock);
	free(table->pids);
	// free(table);
}

void	ft_kill_pids(t_table *table)
{
	size_t	i;

	i = -1;
	while (++i < table->philos_nb)
		kill(table->pids[i], SIGKILL);
}
