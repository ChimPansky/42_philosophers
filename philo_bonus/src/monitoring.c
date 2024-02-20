/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:52:25 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 13:53:58 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_remaining_philos(pid_t *philo_pids, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
		kill(philo_pids[i++], SIGKILL);
}

void	*check_for_sim_end(void *sim_void)
{
	t_simulation	*sim;

	sim = (t_simulation *)sim_void;
	sem_wait(sim->sim_end_sem);
	if (!ft_atomic_bool_load(&sim->all_had_enough_meals))
		kill_remaining_philos(sim->philo_pids, sim->num_philos);
	return (NULL);
}
