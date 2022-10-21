/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:01:31 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/21 09:21:22 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* *************** ***************           *************** *************** */
/*                                  INCLUDES                                 */
/* *************** ***************           *************** *************** */
# include <fcntl.h> /* For O_* constants */
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h> /* For mode constants */
# include <sys/time.h>
# include <unistd.h>

// For time management
# include <sys/time.h>

// For threading
# include <pthread.h>

/* *************** ***************           *************** *************** */
/*                                   MACROS                                  */
/* *************** ***************           *************** *************** */
# define ERROR "Error!"
# define ERRARG "Error! Please check your args"
# define ERRMAL "Error! Somthing went wrong while trying to malloc\n"
# define ERRHLP "Error! Please enter just <help> to get help!"

/* ***** MOVES ***** */
# define EATING "🍔 is eating 🍔"
# define SLEEPING "😴 is sleeping 😴"
# define THINKING "🤔 is thinking 🤔"
# define CHOP1 "🍴 has taken the  first chopstick 🍴"
# define CHOP2 "🍴 has taken the second chopstick 🍴"
# define DEAD "💀☠️ IS DEAD 💀☠️"

/* ***** COLORS ***** */
# define RESET "\e[0m"
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGREEN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLUE "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYAN "\e[1;36m"
# define BWHT "\e[1;37m"

/* ***** HELP MESSAGE ***** */
# define HELP "The number of argments must be 4 or 5:\n\
- arg1 number_of_philosophers\n\
- arg2 time_to_die\n\
- arg3 time_to_eat\n\
- arg4 time_to_sleep\n\
- arg5 number_of_times_each_philosopher_must_eat (optional)"

/* *************** ***************           *************** *************** */
/*                                   STRUCTS                                 */
/* *************** ***************           *************** *************** */

typedef struct s_philos
{
	pid_t			pid;
	size_t			id;
	pthread_t		death_reaper;
	size_t			times_ate;
	size_t			last_meal;
	struct s_table	*table;
}					t_philos;

typedef struct s_table
{
	pthread_t		death_reaper;
	size_t			n_process;
	size_t			philos_nb;
	size_t			ultimatum;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			repeat_time;
	size_t			is_philos_dead;
	time_t			time_begin;
	size_t			count_eat;
	pid_t			*pids;
	sem_t			*writing;
	sem_t			*chops;
}					t_table;

/* *************** ***************           *************** *************** */
/*                                 FUNCTIONS                                 */
/* *************** ***************           *************** *************** */

/* ***** CHECK_ARGS.c ***** */
bool				args_are_valid(char **argv);
bool				print_args_errors(t_table *table, size_t argc);

/* ***** INIT.c ***** */
bool				init_table(size_t argc, char **argv, t_table *table);

/* ***** LOGS.c ***** */
bool				msg_error(char *str);
bool				print_output(t_table *table, size_t id, char *color,
						char *status);
void				start_some_delay(time_t start_time);

/* ***** MOVES.c ***** */
void				eat(t_table *table, t_philos *philo);

/* ***** THREADING.c ***** */
bool				creating_pids(t_table *table);
void				waiting(t_table *table);
void				ft_kill_pids(t_table *table);

/* ***** ROUTINE.c ***** */
bool				launch_simulation(t_table *table, size_t i);
void				*death_reaper(void *args);
bool				init_philos(t_table *table, t_philos *philos, size_t i);

/* ***** UTILS.c ***** */
size_t				ft_strlen(char *str);
size_t				ft_atol(const char *str);
time_t				get_time(void);
void				create_delay(time_t time);
size_t				time_range(time_t time);

// void	ft_simulation(t_table *table, int i);
void				ft_print(t_table *table, t_philos *philo, char *str);
void				ft_error(int error, t_table *table);

#endif