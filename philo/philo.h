/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/12 12:48:32 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include "stdbool.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define SUCCESS 0
# define FAILURE !SUCCESS
# define USEC_MULTIPLIER 1000

typedef struct	s_simulation
{
	int				num_philos;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				num_philos_w_enough_meals;
	bool			all_are_alive;
	pthread_mutex_t	mx_num_philos_w_enough_meals;
	pthread_mutex_t	mx_all_are_alive;
	pthread_mutex_t	mx_logging;
	pthread_mutex_t	*mx_forks;

}				t_simulation;

typedef struct	s_philo{
	pthread_t		pthread;
	int				index;
	long			time_of_beginning_of_last_meal;
	int				number_of_meals_eaten;
	t_simulation	*simulation;
}				t_philo;

// utils.c
void	ft_putstr_fd(char *s, int fd);
int		convert_str_to_int(char *str_to_convert, int *target);

// error_handling.c
int	ph_perror(int error_nr, char *error_info);

#endif
