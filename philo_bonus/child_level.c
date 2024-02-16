/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:23:56 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/16 22:40:34 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

bool	print_log_message(t_simulation *sim, char *log_event,
		long timestamp, bool unlock)
{
	sem_wait(sim->logging_sem);
	printf("%ld P%d %s\n", timestamp, sim->philo_index + 1, log_event);
	dprintf(g_log_fd, "%ld P%d %s\n", timestamp, sim->philo_index + 1, log_event);	// TODO: remove logging
	if (unlock)
		sem_post((sim->logging_sem));
	return (true);
}


static bool	check_if_philo_had_enough_meals(t_simulation *sim)
{
	if (sim->number_of_times_each_philosopher_must_eat == -1)
		return (false);
	if (sim->number_of_meals_eaten >=
		sim->number_of_times_each_philosopher_must_eat)
		{
			dprintf(g_log_fd, "CHILD: P%d HAD ENOUGH TO EAT\n", sim->philo_index + 1);
			return (true);
		}
	return (false);
}

static void	*routine_has_philo_died(void *sim_void)
{
	t_simulation	*sim;

	sim = (t_simulation *)sim_void;
	while (!sim->philo_had_enough)
	{
		if ((get_current_time_ms() -
			ft_atomic_long_load(&sim->time_of_beginning_of_last_meal))
			>= sim->time_to_die)
		{
			print_log_message(sim, LOG_DYING, get_current_sim_time(sim), false);
			sem_post(sim->sim_end_sem); // this will tell parent to kill EVERYBODY
			break ;
		}
		usleep(1);	// TODO: adjust time
	}
	return (NULL);
}

static void	eat_spaghetti(t_simulation *sim)
{
	long	cur_sim_time;

	sem_wait(sim->fork_sem);
	print_log_message(sim, LOG_TAKING_FORK, get_current_sim_time(sim), true);
	sem_wait(sim->fork_sem);
	cur_sim_time = get_current_sim_time(sim);
	print_log_message(sim, LOG_TAKING_FORK, cur_sim_time, true);

	dprintf(g_log_fd, "CHILD: P%d; TIME SINCE BOF_LAST_MEAL: %lu\n",	// TODO: Remove
	sim->philo_index + 1,
	(get_current_time_ms()  - ft_atomic_long_load(&sim->time_of_beginning_of_last_meal)));

	print_log_message(sim, LOG_EATING, cur_sim_time, true);
	ft_atomic_long_store(&sim->time_of_beginning_of_last_meal,
	sim->start_time + cur_sim_time);

	dprintf(g_log_fd, "CHILD: P%d; TIME OF BOF_LAST_MEAL: %lu\n",	// TODO: Remove
	sim->philo_index + 1,
	((ft_atomic_long_load(&sim->time_of_beginning_of_last_meal) - sim->start_time)));

	usleep(sim->time_to_eat * USEC_MULTIPLIER);
	sim->number_of_meals_eaten++;
	sem_post(sim->fork_sem);
	sem_post(sim->fork_sem);
}

static void	sleep_well(t_simulation *sim)
{
	print_log_message(sim, LOG_SLEEPING, get_current_sim_time(sim), true);
	usleep(sim->time_to_sleep * USEC_MULTIPLIER);
}

static void	think_thoroughly(t_simulation *sim)
{
	print_log_message(sim, LOG_THINKING, get_current_sim_time(sim), true);
	usleep(1);
}

void	synchronise_start_time(t_simulation *sim)
{
	long	delay;

	delay = sim->start_time - get_current_time_ms();
	if (delay < 1)
		return ;
	usleep(delay * USEC_MULTIPLIER);
}

int		eat_sleep_think_in_child(t_simulation *sim)
{
	pthread_t	child_monitor;

	if (pthread_create(&child_monitor, NULL, &routine_has_philo_died, (void *)sim) != SUCCESS)
		return (ph_perror(ERRNO_PTHREAD, "eat_slee_think_in_child: create monitor"), FAILURE);

	synchronise_start_time(sim);
	while (1 && sim->number_of_times_each_philosopher_must_eat != 0)
	{
		eat_spaghetti(sim);
		if (check_if_philo_had_enough_meals(sim))
		{
			sim->philo_had_enough = true;
			pthread_join(child_monitor, NULL);
			destroy_sim(sim);
			exit(EXIT_SUCCESS);
		}
		sleep_well(sim);
		think_thoroughly(sim);
	}
	return (SUCCESS);
}
