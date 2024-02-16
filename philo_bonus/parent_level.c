/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_level.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:34 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/16 19:02:47 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// pgrep -f philo_bonus | xargs kill 	// TOTO:REMOVE

static void	kill_remaining_philos(t_philo *philo_processes, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		dprintf(g_log_fd, "PARENT: KILLING CHILD NO %d\n", i);
		kill(philo_processes[i++].child_pid, SIGKILL);
	}
		// catch error?
		// what if u send kill signal to a dead process? i think it's fine
}

static void	*check_for_sim_end(void *sim_void)
{
	t_simulation	*sim;

	sim = (t_simulation *)sim_void;

	dprintf(g_log_fd, "PARENT_MONITOR: WAITING FOR SIM_END\n");
	sem_wait(sim->sim_end_sem);
	if (!sim->all_had_enough_meals)
		kill_remaining_philos(sim->philo_processes, sim->num_philos);
	return (NULL);
}

static int	start_philo_processes(t_simulation *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		dprintf(g_log_fd, "PARENT: STARTING PHILO_PROCESSES\n");
		philo[i].child_pid = fork();
		if (philo[i].child_pid == -1)
		{
			kill_remaining_philos(philo, i);
			return (ph_perror(ERRNO_FORK, "create_philo_processes"), FAILURE);
		}
		if (philo[i].child_pid == 0)
		{
			dprintf(g_log_fd, "CHILD NO %d: STARTING EAT/SLEEP/THINK\n", i);
			eat_sleep_think_in_child(sim);
			break ;
		}
		sim->philo_index++;
		i++;
	}
	return (SUCCESS);
}

void	wait_philo_processes(t_simulation *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		dprintf(g_log_fd, "PARENT: WAITING FOR PHILO_PROCESSES\n");
		waitpid(philo[i++].child_pid, NULL, 0);
		if (i == sim->num_philos)
			sim->all_had_enough_meals = true;
	}
	sem_post(sim->sim_end_sem);
}

int	run_sim_in_parent(t_simulation *sim)
{
	t_philo		philo[sim->num_philos];
	pthread_t	parent_monitor;

	if (pthread_create(&parent_monitor, NULL,	&check_for_sim_end, (void *)sim) != SUCCESS)
		return (ph_perror(ERRNO_PTHREAD, "run_sim_in_parent: create monitor"));
	if (start_philo_processes(sim, philo) != SUCCESS)
		return (pthread_join(parent_monitor, NULL), FAILURE);
	if (philo[sim->philo_index].child_pid != 0)
	{
		wait_philo_processes(sim, philo);
		pthread_join(parent_monitor, NULL);
	}
	return (SUCCESS);
}
