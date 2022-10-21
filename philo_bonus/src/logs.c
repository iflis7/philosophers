/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:26 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/21 09:18:44 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	sem_wait(table->writing);
	printf("%s%-10ld %-3zu %-30s%s\n", color, present, id, status, RESET);
	sem_post(table->writing);
	return (true);
}

void	start_some_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}
