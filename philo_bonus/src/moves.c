/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:38 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/21 09:33:05 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	eat(t_table *table, t_philos *philo)
{
	sem_wait(table->chops);
	print_output(table, philo->id, BBLUE, CHOP1);
	sem_wait(table->chops);
	print_output(table, philo->id, BBLUE, CHOP2);
	philo->last_meal = get_time();
	print_output(table, philo->id, BGREEN, EATING);
	create_delay(table->time_to_eat);
	sem_post(table->chops);
	sem_post(table->chops);
}
