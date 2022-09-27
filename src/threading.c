/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:43:13 by hsaadi            #+#    #+#             */
/*   Updated: 2022/09/27 15:33:48 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_bool	threading(t_master *master)
{
	size_t	i;

	i = 0;
	master->time_begin = get_time() + (master->philo_nb * 10);
	if (pthread_mutex_init(&master->writing_lock, NULL) != 0)
		return (False);
	// start_delay(master->time_begin);
	while (i < master->philo_nb)
	{
		pthread_mutex_lock(&master->writing_lock);
		master->thread_nb = i;
		pthread_mutex_unlock(&master->writing_lock);
		if (pthread_create(&master->philos[i].thread, NULL, &routine, (void *)master) != 0)
			return (False);
		// usleep(1000);
		i++;
	}
	// if (pthread_create(&master->maestro, NULL, &routine_maestro,
	// 		(void *)master) != 0)
	// 	return (False);
	// usleep(500);
	if (join_threads(master) != 0)
		return (False);
	return (True);
}

t_bool	join_threads(t_master *master)
{
	size_t	i;

	i = 0;
	while (i < master->philo_nb)
	{
		if (pthread_join(master->philos[i].thread, NULL) != 0)
			return (False);
		i++;
	}
	// if (pthread_join(master->maestro, NULL) != 0)
	// 	return (False);
	return (True);
}
