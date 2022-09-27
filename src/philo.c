/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:30:48 by hsaadi            #+#    #+#             */
/*   Updated: 2022/09/27 13:30:58 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	size_t		i;
	t_master	*master;

	i = 0;
	i = 0;
	if (argc == 5 || argc == 6)
	{
		args_are_valid(argv);
		init_master(argc, argv, &master);
		// routine_maestro(master);
		// while(1)
		// is_philo_dead(master, &i);
		threading(master);
		// while (1)
		// {
		// }
	}
	return (0);
}
