/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:38 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 00:46:18 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_eating(t_table *table, t_philos *philo)
{
	sem_wait(table->chops);
	print_output(table, philo->id, BBLUE, CHOPSTICK1);
	sem_wait(table->chops);
	print_output(table, philo->id, BBLUE, CHOPSTICK2);
	philo->time_to_die = get_time();
	print_output(table, philo->id, BGREEN, EATING);
	create_delay(table->time_to_eat);
	sem_post(table->chops);
	sem_post(table->chops);
}
