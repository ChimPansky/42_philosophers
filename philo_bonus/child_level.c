/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:23:56 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/18 18:49:26 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic/lib_atomic.h"
#include "philo_bonus.h"
#include <stdlib.h>

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

static void	*routine_has_philo_died(void *sim_void)
{
	t_simulation	*sim;

	sim = (t_simulation *)sim_void;
	usleep(sim->time_to_die * USEC_MULTIPLIER / 2);
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

static void	eat_spaghetti(t_simulation *sim)
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

static void	sleep_and_think(t_simulation *sim)
{
	print_log_message(sim, LOG_SLEEPING, true);
	usleep(sim->time_to_sleep * USEC_MULTIPLIER);
	print_log_message(sim, LOG_THINKING, true);
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

	if (pthread_create(&child_monitor, NULL,
			&routine_has_philo_died, (void *)sim) != SUCCESS)
	{
		ph_perror(ERRNO_PTHREAD, "eat_sleep_think_in_child: create monitor");
		return ;
	}
	synchronise_start_time(sim);
	ft_atomic_long_store(&sim->time_of_beginning_of_last_meal, sim->start_time);
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
