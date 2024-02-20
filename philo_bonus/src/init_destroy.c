/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:47:41 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 14:01:13 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_simulation *sim)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_FORK_PAIR);
	sem_unlink(SEM_LOGGING);
	sem_unlink(SEM_SIM_END);
	sim->fork_sem = sem_open(SEM_FORKS, O_CREAT, 0644, sim->num_philos);
	sim->fork_pair_sem = sem_open(SEM_FORK_PAIR, O_CREAT, 0644, 1);
	sim->logging_sem = sem_open(SEM_LOGGING, O_CREAT, 0644, 1);
	sim->sim_end_sem = sem_open(SEM_SIM_END, O_CREAT, 0644, 0);
	if (sim->fork_sem == SEM_FAILED || sim->fork_pair_sem == SEM_FAILED
		|| sim->logging_sem == SEM_FAILED || sim->sim_end_sem == SEM_FAILED)
		return (FAILURE);
	return (SUCCESS);
}

int	init_ft_atomics(t_simulation *sim)
{
	if (ft_atomic_long_init(&sim->time_of_beginning_of_last_meal, 0)
		!= SUCCESS)
		return (FAILURE);
	if (ft_atomic_bool_init(&sim->philo_had_enough, false) != SUCCESS)
		return (FAILURE);
	if (ft_atomic_bool_init(&sim->all_had_enough_meals, false) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

void	destroy_semaphores(t_simulation *sim)
{
	if (sem_close(sim->fork_sem) == -1)
		ph_perror(ERRNO_SEM_DESTROY, "destroy_simulation: "SEM_FORKS);
	sem_unlink(SEM_FORKS);
	if (sem_close(sim->fork_pair_sem) == -1)
		ph_perror(ERRNO_SEM_DESTROY, "destroy_simulation: "SEM_FORK_PAIR);
	sem_unlink(SEM_FORK_PAIR);
	if (sem_close(sim->logging_sem) == -1)
		ph_perror(ERRNO_SEM_DESTROY, "destroy_simulation: "SEM_LOGGING);
	sem_unlink(SEM_LOGGING);
	if (sem_close(sim->sim_end_sem) == -1)
		ph_perror(ERRNO_SEM_DESTROY, "destroy_simulation: "SEM_SIM_END);
	sem_unlink(SEM_SIM_END);
}

void	destroy_ft_atomics(t_simulation *sim)
{
	if (ft_atomic_long_destroy(&sim->time_of_beginning_of_last_meal)
		!= SUCCESS)
		ph_perror(ERRNO_MUTEX_DESTROY, "destroy_simulation: beg_of_last_meal");
	if (ft_atomic_bool_destroy(&sim->philo_had_enough) != SUCCESS)
		ph_perror(ERRNO_MUTEX_DESTROY, "destroy_simulation: philo_had_enough");
	if (ft_atomic_bool_destroy(&sim->all_had_enough_meals) != SUCCESS)
		ph_perror(ERRNO_MUTEX_DESTROY,
			"destroy_simulation: all_had_enough_meals");
}

void	destroy_sim(t_simulation *sim)
{
	destroy_semaphores(sim);
	destroy_ft_atomics(sim);
}
