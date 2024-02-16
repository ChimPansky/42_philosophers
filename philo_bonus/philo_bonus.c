/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:22:53 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/16 22:40:44 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_sim(t_simulation *sim)
{
	if (sem_close(sim->fork_sem) == -1)
		ph_perror(ERRNO_SEM_DESTROY, "destroy_simulation: "SEM_FORKS);
	sem_unlink(SEM_FORKS);
	if (sem_close(sim->logging_sem) == -1)
		ph_perror(ERRNO_SEM_DESTROY, "destroy_simulation: "SEM_LOGGING);
	sem_unlink(SEM_LOGGING);
	if (sem_close(sim->sim_end_sem) == -1)
		ph_perror(ERRNO_SEM_DESTROY, "destroy_simulation: "SEM_SIM_END);
	sem_unlink(SEM_SIM_END);
	if (ft_atomic_long_destroy(&sim->time_of_beginning_of_last_meal) == -1)
		ph_perror(ERRNO_MUTEX_DESTROY, "destroy_simulation: beg_of_last_meal");
}

static int	init_sim(t_simulation *sim)		// TODO: mb split up into init sems and init atomic...
{
	// need to allocate for sems?
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_LOGGING);
	sem_unlink(SEM_SIM_END);
	sim->fork_sem = sem_open(SEM_FORKS, O_CREAT, 0644, sim->num_philos);
	if (sim->fork_sem == SEM_FAILED)
		return (ph_perror(ERRNO_SEM_OPEN, "init_simulation: "SEM_FORKS),
			destroy_sim(sim), FAILURE);
	sim->logging_sem = sem_open(SEM_LOGGING, O_CREAT, 0644, 1);
	if (sim->logging_sem == SEM_FAILED)
		return (ph_perror(ERRNO_SEM_OPEN, "init_simulation: "SEM_LOGGING),
			destroy_sim(sim), FAILURE);
	sim->sim_end_sem = sem_open(SEM_SIM_END, O_CREAT, 0644, 0);
	if (sim->sim_end_sem == SEM_FAILED)
		return (ph_perror(ERRNO_SEM_OPEN, "init_simulation: "SEM_SIM_END),
			destroy_sim(sim), FAILURE);
	sim->start_time = get_current_time_ms() + 10;
	if (ft_atomic_long_init(&sim->time_of_beginning_of_last_meal,
		sim->start_time) != SUCCESS)
		return (ph_perror(ERRNO_MUTEX_CREATE, "init_simulation: beg_of_last_meal"),
			destroy_sim(sim), FAILURE);
	sim->philo_index = 0;
	sim->number_of_meals_eaten = 0;
	sim->all_had_enough_meals = false;
	sim->philo_had_enough = false;
	return (SUCCESS);
}

int g_log_fd;	// TODO: remove
int	main(int argc, char **argv)
{
	t_simulation	sim;

	g_log_fd = open("debug.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644); // TODO: REMOVE

	if (read_args_into_sim(&sim, argc, argv) == FAILURE)
		return (FAILURE);
	if (init_sim(&sim) == FAILURE)
		return (FAILURE);
	if (run_sim_in_parent(&sim) == FAILURE)
		return (destroy_sim(&sim), FAILURE);
	destroy_sim(&sim);
	return (SUCCESS);
}
