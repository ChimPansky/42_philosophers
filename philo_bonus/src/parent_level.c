/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_level.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:34 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 13:53:10 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_philo_processes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		sim->philo_pids[i] = fork();
		if (sim->philo_pids[i] == -1)
		{
			kill_remaining_philos(sim->philo_pids, i);
			return (ph_perror(ERRNO_FORK, "create_philo_processes"), FAILURE);
		}
		if (sim->philo_pids[i] == 0)
			eat_sleep_think_in_child(sim);
		sim->philo_index++;
		i++;
	}
	return (SUCCESS);
}

static void	wait_philo_processes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		waitpid(0, NULL, 0);
		if (i == sim->num_philos - 1)
			ft_atomic_bool_store(&sim->all_had_enough_meals, true);
		i++;
	}
	sem_post(sim->sim_end_sem);
}

static void	init_philo_processes(pid_t *pids, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
		pids[i++] = 0;
}

int	run_sim_in_parent(t_simulation *sim)
{
	pid_t		*philos;
	pthread_t	parent_monitor;

	philos = malloc(sizeof(pid_t) * sim->num_philos);
	if (!philos)
		return (ph_perror(ERRNO_MALLOC, "run_sim_in_parent: philos"), FAILURE);
	parent_monitor = 0;
	init_philo_processes(philos, sim->num_philos);
	sim->philo_pids = philos;
	if (create_philo_processes(sim) != SUCCESS)
		return (free(philos), pthread_join(parent_monitor, NULL), FAILURE);
	if (pthread_create(&parent_monitor, NULL, &check_for_sim_end, (void *)sim)
		!= SUCCESS)
		return (free(philos),
			ph_perror(ERRNO_PTHREAD, "run_sim_in_parent: create monitor"));
	wait_philo_processes(sim);
	pthread_join(parent_monitor, NULL);
	return (free(philos), SUCCESS);
}
