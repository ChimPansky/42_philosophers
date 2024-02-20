/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:35:00 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/18 18:37:17 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	validate_args(t_simulation *sim)
{
	if (sim->num_philos < 0)
		return (ph_perror(ERRNO_ARG_NOT_INT,
				"Argument validation: num_philos"), FAILURE);
	if (sim->num_philos < 1)
		return (ph_perror(ERRNO_ARG_NO_PHILO,
				"Argument validation"), FAILURE);
	if (sim->time_to_die < 0)
		return (ph_perror(ERRNO_ARG_NOT_LONG,
				"Argument validation: time_to_die"), FAILURE);
	if (sim->time_to_eat < 0)
		return (ph_perror(ERRNO_ARG_NOT_LONG,
				"Argument validation: time_to_eat"), FAILURE);
	if (sim->time_to_sleep < 0)
		return (ph_perror(ERRNO_ARG_NOT_LONG,
				"Argument validation: time_to_sleep"), FAILURE);
	if (sim->number_of_times_each_philosopher_must_eat != -1
		&& sim->number_of_times_each_philosopher_must_eat < 0)
		return (ph_perror(ERRNO_ARG_NOT_INT,
				"Argument validation: num_times_philo_must_eat"), FAILURE);
	return (SUCCESS);
}

int	read_args_into_sim(t_simulation *sim, int argc, char **argv)
{
	if (argc < 5)
		return (ph_perror(ERRNO_ARGS_NOT_ENOUGH, "Argument validation"),
			FAILURE);
	if (argc > 6)
		return (ph_perror(ERRNO_ARGS_TOO_MANY,
				"Argument validation"), FAILURE);
	if (!ft_str_isnum(argv[1]) || !ft_str_isnum(argv[2])
		|| !ft_str_isnum(argv[3]) || !ft_str_isnum(argv[4])
		|| (argc == 6 && !ft_str_isnum(argv[5])))
		return (ph_perror(ERRNO_ARG_NOT_NUM, "Argument validation"), FAILURE);
	sim->num_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		sim->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		sim->number_of_times_each_philosopher_must_eat = -1;
	return (validate_args(sim));
}
