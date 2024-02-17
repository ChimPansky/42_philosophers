/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/17 22:58:56 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H


# include "ph_messages.h"
# include "stdbool.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
# include "lib_atomic/lib_atomic.h"
# include <pthread.h>
# include <bits/pthreadtypes.h>
# include "semaphore.h"
#include <sys/types.h>
#include <sys/wait.h>

# include "fcntl.h"	//TODO: remove

# define SUCCESS 0
# define FAILURE !SUCCESS
# define USEC_MULTIPLIER 1000

# define LOG_TAKING_FORK "has taken a fork"
# define LOG_EATING "is eating"
# define LOG_SLEEPING "is sleeping"
# define LOG_THINKING "is thinking"
# define LOG_DYING "died"

# define SEM_FORKS "forks_on_the_table"
# define SEM_ODD_START "odd_start"
# define SEM_LOGGING "logging_messages"
# define SEM_SIM_START "start_simulation"
# define SEM_SIM_END "simulation_end"

extern int g_log_fd;	// TODO: remove

typedef enum e_exit_codes
{
	EXIT_CHILD_DIED,
	EXIT_CHILD_HAD_ENOUGH_MEALS
}			t_exit_codes ;

typedef struct	s_simulation
{
	pid_t				*philo_pids;	//just a pointer to an array with the pids
	sem_t				*fork_sem;
	sem_t				*odd_start_sem;
	sem_t				*logging_sem;
	sem_t				*sim_start_sem;
	sem_t				*sim_end_sem;
	int					num_philos;
	int					philo_index;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	long				start_time;
	t_ft_atomic_long	time_of_beginning_of_last_meal;
	t_ft_atomic_bool	philo_had_enough;
	t_ft_atomic_bool	all_had_enough_meals;
	int					number_of_meals_eaten;
	int				log_fd; //TODO: remove
}				t_simulation;

// philo.c
int		main(int argc, char **argv);
void	destroy_sim(t_simulation *sim);

// args_validation.c
int		read_args_into_sim(t_simulation *sim, int argc, char **argv);

// parent_level.c (simulation)
int		run_sim_in_parent(t_simulation *sim);
bool	simulation_end(t_simulation *sim);

// child_level.c
bool	print_log_message(t_simulation *sim, char *log_event, bool unlock);
int		eat_sleep_think_in_child(t_simulation *sim);

// routine.c

// monitoring.c
void	update_sim_end_conditions(t_simulation *sim);

// time.c
long	get_current_time_ms(void);
long	get_current_sim_time(t_simulation *sim);

// utils.c
int		ft_atoi(char *string);
long	ft_atol(char *string);
void	ft_putstr_fd(char *s, int fd);
bool	ft_str_isnum(char *string);

// error_handling.c
int		ph_perror(int error_nr, char *error_info);


#endif
