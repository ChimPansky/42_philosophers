/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:23:56 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 15:03:22 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	print_log_message(t_simulation *sim, char *log_event, bool unlock)
{
	sem_wait(sim->logging_sem);
	printf("%ld P%d %s\n", get_current_sim_time(sim),
		sim->philo_index + 1, log_event);
	if (unlock)
		sem_post((sim->logging_sem));
	return (true);
}

static bool	check_if_philo_had_enough_meals(t_simulation *sim)
{
	if (sim->number_of_times_each_philosopher_must_eat == -1)
		return (false);
	if (sim->number_of_meals_eaten
		>= sim->number_of_times_each_philosopher_must_eat)
		return (true);
	return (false);
}

static void	synchronise_start_time(t_simulation *sim)
{
	long	delay;

	delay = sim->start_time - get_current_time_usec();
	if (delay > 0)
		usleep(delay);
	usleep(sim->philo_index * 300);
}

void	eat_sleep_think_in_child(t_simulation *sim)
{
	pthread_t	child_monitor;

	synchronise_start_time(sim);
	if (pthread_create(&child_monitor, NULL,
			&routine_has_philo_died, (void *)sim) != SUCCESS)
	{
		ph_perror(ERRNO_PTHREAD, "eat_sleep_think_in_child: create monitor");
		return ;
	}
	while (1 && sim->number_of_times_each_philosopher_must_eat != 0)
	{
		eat_spaghetti(sim);
		if (check_if_philo_had_enough_meals(sim))
		{
			ft_atomic_bool_store(&sim->philo_had_enough, true);
			pthread_join(child_monitor, NULL);
			destroy_sim(sim);
			exit(EXIT_SUCCESS);
		}
		sleep_and_think(sim);
	}
	pthread_join(child_monitor, NULL);
	destroy_sim(sim);
	exit(EXIT_SUCCESS);
}
