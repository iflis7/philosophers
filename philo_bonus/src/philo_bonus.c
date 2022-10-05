/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:30:48 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/05 11:35:47 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;
	if (argc == 5 || argc == 6)
	{
		if (!args_are_valid(argv))
			return (-1);
		if (!init_table(argc, argv, &table))
			return (-1);
		if (!threading(&table))
			return (-1);
		if (!destroying_threads(&table))
			return (-1);
		return (0);
	}
}
// philos_free(&table)