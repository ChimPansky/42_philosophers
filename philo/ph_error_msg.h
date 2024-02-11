/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_msg.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/12 00:32:46 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_ERROR_MSG_H
# define PH_ERROR_MSG_H

#include <stdbool.h>
# define ERR_ARGS_NOT_ENOUGH "Not enough arguments."
# define ERR_ARGS_TOO_MANY "Too many arguments."
# define ERR_ARG_NOT_INT "Argument is not an integer"

# define SUCCESS 0
# define FAILURE !SUCCESS

typedef enum e_errors
{
	ER_ARGS_NOT_ENOUGH,
	ER_ARGS_TOO_MANY,
	ER_ARG_NOT_INT,
	ER_COUNT
}			t_errors;

char *error_messages[ER_COUNT];
char[ER_ARGS_NOT_ENOUGH] = "Not enough arguments.";

typedef struct	s_philosophy
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	bool	all_are_alive;
}				t_philosophy;

typedef struct	s_philo{
	int	time_of_beginning_of_last_meal;
	int	number_of_meals_eaten;
}				t_philo;

#endif
