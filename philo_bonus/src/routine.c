/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:54:48 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 15:03:52 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine_has_philo_died(void *sim_void)
{
	t_simulation	*sim;

	sim = (t_simulation *)sim_void;
	while (!ft_atomic_bool_load(&sim->philo_had_enough))
	{
		if ((get_current_time_usec()
				- ft_atomic_long_load(&sim->time_of_beginning_of_last_meal))
			>= sim->time_to_die * USEC_MULTIPLIER)
		{
			print_log_message(sim, LOG_DYING, false);
			sem_post(sim->sim_end_sem);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}

void	sleep_and_think(t_simulation *sim)
{
	print_log_message(sim, LOG_SLEEPING, true);
	usleep(sim->time_to_sleep * USEC_MULTIPLIER);
	print_log_message(sim, LOG_THINKING, true);
}

void	eat_spaghetti(t_simulation *sim)
{
	sem_wait(sim->fork_pair_sem);
	sem_wait(sim->fork_sem);
	print_log_message(sim, LOG_TAKING_FORK, true);
	sem_wait(sim->fork_sem);
	print_log_message(sim, LOG_TAKING_FORK, true);
	sem_post(sim->fork_pair_sem);
	print_log_message(sim, LOG_EATING, true);
	ft_atomic_long_store(&sim->time_of_beginning_of_last_meal,
		get_current_time_usec());
	usleep(sim->time_to_eat * USEC_MULTIPLIER);
	sim->number_of_meals_eaten++;
	sem_post(sim->fork_sem);
	sem_post(sim->fork_sem);
}
