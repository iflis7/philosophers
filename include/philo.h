#ifndef PHILO_H
#define PHILO_H

/* ***** INCLUDES ***** */
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// For time management
#include <sys/time.h>

// For threading
#include <pthread.h>

/* ***** MACROS ***** */
#define ERROR "Error!"
#define ERRARG "Error! Please check your args"
#define ERRMAL "Error! Somthing went wrong while trying to malloc\n"
#define ERRHLP "Error! Please enter just <help> to get help!"

/* ***** MOVES ***** */
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define FORK "has taken a fork"
#define DIED "died ☠️"

/* ***** COLORS ***** */
#define BRED "\e[1;31m"
#define PINK "\e[0;38;5;199m"
#define GREEN "\e[0;32m"
#define BLUE "\e[0;34m"
#define G_BLUE "\e[0;38;5;24m"
#define B_BLUE "\e[1;34m"
#define G_CYAN "\e[0;38;5;44m"

/*
** Help message
*/
#define HELP "The number of argments must be 4 or 5:\n\
- arg1 number_of_philosophers\n\
- arg2 time_to_die\n\
- arg3 time_to_eat\n\
- arg4 time_to_sleep\n\
- arg5 number_of_times_each_philosopher_must_eat (optional)"

#endif