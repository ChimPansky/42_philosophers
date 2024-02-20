/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:22:53 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 15:02:00 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_sim(t_simulation *sim)
{
	sim->philo_index = 0;
	sim->number_of_meals_eaten = 0;
	if (init_semaphores(sim) != SUCCESS)
		return (ph_perror(ERRNO_SEM_OPEN, "init_simulation"), FAILURE);
	if (init_ft_atomics(sim) != SUCCESS)
		return (destroy_semaphores(sim),
			ph_perror(ERRNO_MUTEX_CREATE, "init_simulation"), FAILURE);
	sim->start_time = get_current_time_usec()
		+ 100000 + (sim->num_philos * 1000);
	ft_atomic_long_store(&sim->time_of_beginning_of_last_meal,
		sim->start_time);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (read_args_into_sim(&sim, argc, argv) == FAILURE)
		return (FAILURE);
	if (init_sim(&sim) == FAILURE)
		return (FAILURE);
	if (run_sim_in_parent(&sim) == FAILURE)
		return (destroy_sim(&sim), FAILURE);
	destroy_sim(&sim);
	return (SUCCESS);
}
