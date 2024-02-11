/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/11 23:33:37 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "pthread.h"
# include <bits/pthreadtypes.h>
# include "stdbool.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE !SUCCESS

typedef struct	s_simulation
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}				t_simulation;

typedef struct	s_philo{
	int	time_of_beginning_of_last_meal;
	int	number_of_meals_eaten;
}				t_philo;

// utils.c
void	ft_putstr_fd(char *s, int fd);
int		convert_str_to_int(char *str_to_convert, int *target);

#endif
