#ifndef PHILO_H
# define PHILO_H

/* *************** INCLUDES *************** */
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
# define EATING "🍔 is eating 🍔"
# define SLEEPING "😴 is sleeping 😴"
# define THINKING "🤔 is thinking 🤔"
# define CHOPSTICK1 "🍴 has taken the  first chopstick 🍴"
# define CHOPSTICK2 "🍴 has taken the second chopstick 🍴"
# define DEAD "💀☠️ DEAD 💀☠️"

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
/*                                    ENUMS                                  */
/* *************** ***************           *************** *************** */
typedef enum e_bool
{
	False,
	True,
}					t_bool;

/* *************** ***************           *************** *************** */
/*                                   STRUCTS                                 */
/* *************** ***************           *************** *************** */
typedef struct s_chopstick
{
	size_t			left;
	size_t			right;
}					t_chopstick;

typedef struct s_master
{
	size_t			philo_nb;
	time_t			time_to_eat;
	time_t			ultimatum;
	time_t			time_to_sleep;
	time_t			time_begin;
	size_t			repeat_time;
	size_t			thread_nb;
	size_t			is_philo_dead;
	pthread_t		maestro;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	writing_lock;
	struct s_philo	*philos;
}					t_master;

typedef struct s_philo
{
	pthread_t		thread;
	size_t			id;
	size_t			times_ate;
	time_t			time_to_die;
	size_t			status;
	pthread_mutex_t	eating_lock;
	t_chopstick		chops;
	t_master		master;
}					t_philo;

/* *************** ***************           *************** *************** */
/*                                 FUNCTIONS                                 */
/* *************** ***************           *************** *************** */

/* ***** CHECK_ARGS.c ***** */
void				args_are_valid(char **argv);
void				print_args_errors(t_master *master, size_t argc);

/* ***** INIT.c ***** */
void				init_master(size_t argc, char **argv, t_master **master);

/* ***** LOGS.c ***** */
void				msg_error(char *str);
t_bool				print_output(t_master *master, size_t id, char *color,
						char *status);

/* ***** UTILS.c ***** */
size_t				ft_strlen(char *str);
size_t				ft_atol(const char *str);
time_t				get_time(void);
time_t				time_range(time_t time);

/* ***** THREADING.c ***** */
t_bool				threading(t_master *master);
t_bool				join_threads(t_master *master);

/* ***** ROUTINE.c ***** */
void				*routine(void *args);
t_bool				execute_routine(t_master *master, size_t i);
void				*routine_maestro(void *args);

/* ***** MOVES.c ***** */
t_bool				eat(t_master *master, size_t i);
t_bool				go_sleep(t_master *master, size_t i);
t_bool				think(t_master *master, size_t i);
t_bool				drop_chops(t_master *master, int i);
t_bool				is_philo_dead(t_master *master, size_t *i);

#endif