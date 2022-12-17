/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:01:31 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/26 18:54:21 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* *************** ***************           *************** *************** */
/*                                  INCLUDES                                 */
/* *************** ***************           *************** *************** */
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
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
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define SLEEPING1 "is sleeping 1"
# define THINKING "is thinking"
# define CHOPSTICK1 "has taken the  first chopstick"
# define CHOPSTICK2 "has taken the second chopstick"
# define DEAD "IS DEAD"

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
typedef struct s_chopstick
{
	size_t			left;
	size_t			right;
}					t_chopstick;

typedef struct s_philos
{
	pthread_t		thread;
	size_t			id;
	size_t			times_ate;
	size_t			time_to_die;
	t_chopstick		chops;
	struct s_table	*table;
}					t_philos;

typedef struct s_table
{
	size_t			n_thread;
	size_t			philos_nb;
	size_t			ultimatum;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			repeat_time;
	size_t			is_philos_dead;
	time_t			time_begin;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	writing_lock;
	pthread_t		maestro;
	t_philos		*philos;
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
size_t				ft_strlen(char *str);
bool				msg_error(char *str);
void				philos_free(t_table *table);
bool				print_output(t_table *table, size_t id, char *color,
						char *status);

/* ***** MOVES.c ***** */
bool				eat(t_table *table, size_t i);
bool				go_to_sleep(t_table *table, size_t i);
bool				think(t_table *table, size_t i);
bool				is_philo_dead(t_table *table, size_t *i);
bool				drop_chops(t_table *table, size_t i);

/* ***** ROUTINE.c ***** */
void				*routine(void *args);
size_t				run_routine(t_table *table, size_t i);
void				*maestro_routine(void *args);

/* ***** THREADING.c ***** */
bool				threading(t_table *table);
bool				joining_threads(t_table *table);
bool				destroying_threads(t_table *table);

/* ***** UTILS.c ***** */
size_t				ft_atol(const char *str);
time_t				get_time(void);
time_t				time_range(time_t time);
void				create_delay(time_t time);
void				start_some_delay(time_t start_time);

#endif