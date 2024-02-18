/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_level.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:34 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/18 18:50:59 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic/lib_atomic.h"
#include "philo_bonus.h"

// catch error?
		// what if u send kill signal to a dead process? i think it's fine
static void	kill_remaining_philos(pid_t *philo_pids, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
		kill(philo_pids[i++], SIGKILL);
}

static void	*check_for_sim_end(void *sim_void)
{
	t_simulation	*sim;

	sim = (t_simulation *)sim_void;
	sem_wait(sim->sim_end_sem);
	if (!ft_atomic_bool_load(&sim->all_had_enough_meals))
		kill_remaining_philos(sim->philo_pids, sim->num_philos);
	return (NULL);
}

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

void	wait_philo_processes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		waitpid(0, NULL, 0);
		if (i == sim->num_philos - 1)
			ft_atomic_bool_store(&sim->all_had_enough_meals, true); // TODO: only true if they have not been killed by signal... (check with WIFEXITED/WIFSIGNALED...)
		i++;
	}
	sem_post(sim->sim_end_sem);
}

void	init_philo_processes(pid_t *pids, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
		pids[i++] = 0;
}

int	run_sim_in_parent(t_simulation *sim)
{
	pid_t		philo[sim->num_philos];	// TODO: malloc in init_philos and free on destroy
	pthread_t	parent_monitor;

	init_philo_processes(philo, sim->num_philos);
	sim->philo_pids = philo;
	if (create_philo_processes(sim) != SUCCESS)
		return (pthread_join(parent_monitor, NULL), FAILURE);
	if (pthread_create(&parent_monitor, NULL, &check_for_sim_end, (void *)sim) != SUCCESS)
		return (ph_perror(ERRNO_PTHREAD, "run_sim_in_parent: create monitor"));
	wait_philo_processes(sim);
	pthread_join(parent_monitor, NULL);
	return (SUCCESS);
}

// static void	start_philo_processes(t_simulation *sim)
// {
// 	int	i;

// 	i = 0;
// 	long	delay;

// 	delay = sim->start_time - get_current_time_ms();
// 	if (delay > 0)
// 		usleep(delay * USEC_MULTIPLIER);
	// while (i < sim->num_philos)
	// {
	// 	if (i++ % 2 == 0)
	// 	{
	// 		sem_post(sim->even_start_sem);
	// 		//usleep(1);
	// 	}
	// }
	// i = 0;
	// usleep(10000);
	// while (i < sim->num_philos)
	// {
	// 	if (i++ % 2 == 1)
	// 	{
	// 		sem_post(sim->odd_start_sem);
	// 		//usleep(1);
	// 	}
	// }
// }
