/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 13:16:33 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include "stdbool.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
# include "../lib_atomic/lib_atomic.h"
# include "ph_messages.h"
# include <limits.h>

# define SUCCESS 0
# define FAILURE 1
# define USEC_MULTIPLIER 1000

typedef struct s_simulation
{
	int					num_philos;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_think;
	int					number_of_times_each_philosopher_must_eat;
	t_ft_atomic_bool	all_are_alive;
	t_ft_atomic_bool	all_had_enough_meals;
	pthread_mutex_t		logging_guard;
	pthread_mutex_t		*fork_guards;
}				t_simulation;

typedef struct s_philo
{
	pthread_t			pthread;
	int					index;
	t_ft_atomic_long	time_of_beginning_of_last_meal;
	t_ft_atomic_int		number_of_meals_eaten;
	t_ft_atomic_bool	sim_has_ended;
	t_ft_atomic_bool	had_enough_meals;
	t_simulation		*sim;
}				t_philo;

// philo.c
int		main(int argc, char **argv);

// args_validation.c
int		read_args_into_sim(t_simulation *sim, int argc, char **argv);

// sim.c
int		run_simulation(t_simulation *sim);
bool	print_log_message(t_simulation *sim, char *log_event, int philo_nr);
bool	simulation_end(t_simulation *sim);

// routine.c
void	*routine_eat_sleep_think(void *arg);
bool	simulation_end(t_simulation *sim);

// spaghetti.c
bool	eat_spaghetti(t_philo *philo);

// monitoring.c
void	update_sim_end_conditions(t_simulation *sim, t_philo *philos);

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
