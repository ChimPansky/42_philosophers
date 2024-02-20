/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 14:01:29 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "ph_messages.h"
# include "stdbool.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "../lib_atomic/lib_atomic.h"
# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <fcntl.h>
# include "semaphore.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

# define SUCCESS 0
# define FAILURE 1
# define USEC_MULTIPLIER 1000

# define LOG_TAKING_FORK "has taken a fork"
# define LOG_EATING "is eating"
# define LOG_SLEEPING "is sleeping"
# define LOG_THINKING "is thinking"
# define LOG_DYING "died"

# define SEM_FORKS "forks_on_the_table"
# define SEM_FORK_PAIR "fork_pair"
# define SEM_LOGGING "logging_messages"
# define SEM_SIM_END "simulation_end"

typedef struct s_simulation
{
	pid_t				*philo_pids;
	sem_t				*fork_sem;
	sem_t				*fork_pair_sem;
	sem_t				*logging_sem;
	sem_t				*sim_end_sem;
	int					num_philos;
	int					philo_index;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	long				start_time;
	long				time_sync;
	t_ft_atomic_long	time_of_beginning_of_last_meal;
	t_ft_atomic_bool	philo_had_enough;
	t_ft_atomic_bool	all_had_enough_meals;
	int					number_of_meals_eaten;
}			t_simulation;

// philo.c
int		main(int argc, char **argv);

// init_destroy.c
int		init_semaphores(t_simulation *sim);
int		init_ft_atomics(t_simulation *sim);
void	destroy_semaphores(t_simulation *sim);
void	destroy_ft_atomics(t_simulation *sim);
void	destroy_sim(t_simulation *sim);

// args_validation.c
int		read_args_into_sim(t_simulation *sim, int argc, char **argv);

// parent_level.c (simulation)
int		run_sim_in_parent(t_simulation *sim);
bool	simulation_end(t_simulation *sim);

// monitoring.c
void	kill_remaining_philos(pid_t *philo_pids, int num_philos);
void	*check_for_sim_end(void *sim_void);

// child_level.c
bool	print_log_message(t_simulation *sim, char *log_event, bool unlock);
void	eat_sleep_think_in_child(t_simulation *sim);

// routine.c
void	*routine_has_philo_died(void *sim_void);

// monitoring.c
void	update_sim_end_conditions(t_simulation *sim);
void	eat_spaghetti(t_simulation *sim);
void	sleep_and_think(t_simulation *sim);

// time.c
long	get_current_time_ms(void);
long	get_current_time_usec(void);
long	get_current_sim_time(t_simulation *sim);

// utils.c
int		ft_atoi(char *string);
long	ft_atol(char *string);
void	ft_putstr_fd(char *s, int fd);
bool	ft_str_isnum(char *string);

// error_handling.c
int		ph_perror(int error_nr, char *error_info);

#endif
