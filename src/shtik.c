/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shtik.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:07:23 by hsaadi            #+#    #+#             */
/*   Updated: 2022/09/22 15:07:23 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*shtick(void *args)
{
	t_master	*master;
	size_t		i;

	master = (t_master *)args;
	i = master->thread_nb;
	if (master->repeat_time)
	{
		while (master->repeat_time > master->philos[i].times_ate && !master->is_philo_dead)
			execute_shtick(master, i);
	}
	else
	{
		while (!master->is_philo_dead)
		{
			if (!execute_shtick(master, i))
				break ;
		}
	}
	return (NULL);
}


t_bool	execute_shtick(t_master *master, size_t i)
{
	if (!philo_eat(master, i))
		return (False);

	return (True);
}



void	*shtick_check(void *args)
{
	t_master	*master;
	size_t		i;

	master = (t_master *)args;
	i = 0;
	if (master->repeat_time)
	{
		while (master->repeat_time > master->philos[i].times_ate
			&& !master->is_philo_dead)
		{
			if (philo_is_dead(master, &i))
				break ;
		}
	}
	else
	{
		while (master->is_philo_dead == False)
		{
			if (philo_is_dead(master, &i))
				break ;
		}
	}
	return (NULL);
}


t_bool	print_output(t_master *master, size_t id, char *color, char *status)
{
	time_t	present;

	present = delta_time(master->time_begin);
	if (master->is_philo_dead)
		return (False);
	// pthread_mutex_unlock(&master->writing_lock);
	pthread_mutex_lock(&master->writing_lock);
	if (master->is_philo_dead)
	{
		pthread_mutex_unlock(&master->writing_lock);
		return (False);
	}
	else
		printf("%s%-10ld %-3zu %-30s%s\n", color, present, id, status, RESET);
	pthread_mutex_unlock(&master->writing_lock);
	return (True);
}
