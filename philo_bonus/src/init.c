/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:00:49 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/20 00:27:22 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	manage_one_philo(t_table *table)
{
	time_t	present;

	present = 0;
	table->time_begin = get_time();
	sem_wait(table->chops);
	printf("%s%-10ld %-3zu %-30s%s\n", BBLUE, present, table->philos[0].id,
			CHOPSTICK1, RESET);
	usleep(table->ultimatum * 1000);
	present = time_range(table->time_begin);
	printf("%s%-10ld %-3zu %-30s%s\n", BRED, present, table->philos[0].id, DEAD,
			RESET);
	sem_post(table->chops);
	table->is_philos_dead = true;
	return (false);
}

bool	init_semaphore(t_table *table)
{
	sem_unlink("fork_sem");
	sem_unlink("writing_lock");
	table->writing_lock = sem_open("writing_lock", O_CREAT | O_EXCL, 777, 1);
	table->chops = sem_open("fork_sem", O_CREAT | O_EXCL, 777, table->philos_nb);
	if (table->writing_lock <= 0 || table->chops <= 0)
		return (false);
	return (true);
}

bool	init_table(size_t argc, char **argv, t_table *table)
{
	table->philos_nb = ft_atol(argv[1]);
	table->ultimatum = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->repeat_time = ft_atol(argv[5]);
	if (!print_args_errors(table, argc))
		return (false);
	if (!init_semaphore(table))
		return (msg_error(ERRMAL));
	table->is_philos_dead = false;
	// if (table->philos_nb == 1)
	// 	manage_one_philo(table);
	return (true);
}

// void    ft_sleep(long int time_to_stop)
// {
//     long int    delay;

//     while (1)
//     {
//         delay = time_to_stop - ft_get_time();
//         if (delay <= 0)
//             break ;
//         usleep(50);
//     }
// }
