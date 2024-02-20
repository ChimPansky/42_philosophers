/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:24:16 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 10:58:22 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_min(int val1, int val2)
{
	if (val1 < val2)
		return (val1);
	return (val2);
}

static bool	think_thoroughly(t_philo *philo)
{
	if (!print_log_message(philo->sim, LOG_THINKING, philo->index))
		return (false);
	usleep(philo->sim->time_to_think * USEC_MULTIPLIER);
	return (true);
}
// the current_time is sometimes not calculated properly.
static bool	sleep_well(t_philo *philo)
{
	if (!print_log_message(philo->sim, LOG_SLEEPING, philo->index))
		return (false);
	usleep(philo->sim->time_to_sleep * USEC_MULTIPLIER);
	return (true);
}

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	if (philo->index % 2 == 0)
	{
		first_fork = &philo->sim->fork_guards[philo->index];
		second_fork = &philo->sim->fork_guards[
		(philo->index + philo->sim->num_philos - 1)	% philo->sim->num_philos];
	}
	else
	{
		first_fork = &philo->sim->fork_guards[
		(philo->index + philo->sim->num_philos - 1)	% philo->sim->num_philos];
		second_fork = &philo->sim->fork_guards[philo->index];
	}
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}
static bool	take_forks(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	if (philo->index % 2 == 0)
	{
		first_fork = &philo->sim->fork_guards[philo->index];
		second_fork = &philo->sim->fork_guards[
		(philo->index + philo->sim->num_philos - 1)	% philo->sim->num_philos];
	}
	else
	{
		first_fork = &philo->sim->fork_guards[
		(philo->index + philo->sim->num_philos - 1)	% philo->sim->num_philos];
		second_fork = &philo->sim->fork_guards[philo->index];
	}
	pthread_mutex_lock(first_fork);
	if (!print_log_message(philo->sim, LOG_TAKING_FORK, philo->index)
		|| philo->sim->num_philos == 1)	// TODO: diner for one
		return (pthread_mutex_unlock(first_fork), false);
	pthread_mutex_lock(second_fork);
	if (!print_log_message(philo->sim, LOG_TAKING_FORK, philo->index))
		return (pthread_mutex_unlock(first_fork),
			pthread_mutex_unlock(second_fork), false);
	return (true);
}

static bool	eat_spaghetti(t_philo *philo)
{
	if (philo->sim->num_philos == 1) // TODO: dinner for one
		return (false);
	if (!take_forks(philo))
		return (false);
	ft_atomic_long_store(&philo->time_of_beginning_of_last_meal,
		get_current_time_usec());
	if (!print_log_message(philo->sim, LOG_EAT, philo->index))
		return (false);
	usleep(philo->sim->time_to_eat * USEC_MULTIPLIER);
	put_down_forks(philo);
	ft_atomic_int_fetch_add(&philo->number_of_meals_eaten, 1);
	if (philo->sim->number_of_times_each_philosopher_must_eat != -1
		&& ft_atomic_int_load(&philo->number_of_meals_eaten)
		>= philo->sim->number_of_times_each_philosopher_must_eat)
		ft_atomic_bool_store(&philo->had_enough_meals, true);
	return (true);
}

void	synchronise_start_time(t_philo *philo)
{
	long	delay;

	delay = philo->sim->start_time - get_current_time_usec();
	if (delay > 0)
		usleep(delay);
	usleep(philo->index * 300);
}

void	*routine_eat_sleep_think(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchronise_start_time(philo);
	ft_atomic_long_store(&philo->time_of_beginning_of_last_meal,
		philo->sim->start_time);
	while(true && philo->sim->number_of_times_each_philosopher_must_eat != 0)
	{
		if (!eat_spaghetti(philo) || simulation_end(philo->sim))
			break;
		if (!sleep_well(philo) || simulation_end(philo->sim))
			break;
		if (!think_thoroughly(philo) || simulation_end(philo->sim))
			break;
		if (ft_atomic_bool_load(&philo->had_enough_meals) == true)
			break;
	}
	return ((void*)philo);
}
