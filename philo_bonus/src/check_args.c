/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:22:54 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/05 11:38:51 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	args_are_valid(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("%s%s\n", BRED, ERRARG);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	print_args_errors(t_table *table, size_t argc)
{
	if (!table->philos_nb || !table->ultimatum || !table->time_to_eat
		|| !table->time_to_sleep)
	{
		printf("%s%s\n", BRED, ERRARG);
		return (false);
	}
	if (argc == 6 && !table->repeat_time)
	{
		printf("%s%s\n", BRED, ERRARG);
		return (false);
	}
	return (true);
}
