/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:36:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 12:36:44 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->index % 2 == 0)
	{
		first_fork = &philo->sim->fork_guards[philo->index];
		second_fork = &philo->sim->fork_guards[(philo->index
				+ philo->sim->num_philos - 1) % philo->sim->num_philos];
	}
	else
	{
		first_fork = &philo->sim->fork_guards[(philo->index
				+ philo->sim->num_philos - 1) % philo->sim->num_philos];
		second_fork = &philo->sim->fork_guards[philo->index];
	}
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

static bool	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->index % 2 == 0)
	{
		first_fork = &philo->sim->fork_guards[philo->index];
		second_fork = &philo->sim->fork_guards[(philo->index
				+ philo->sim->num_philos - 1) % philo->sim->num_philos];
	}
	else
	{
		first_fork = &philo->sim->fork_guards[(philo->index
				+ philo->sim->num_philos - 1) % philo->sim->num_philos];
		second_fork = &philo->sim->fork_guards[philo->index];
	}
	pthread_mutex_lock(first_fork);
	if (!print_log_message(philo->sim, LOG_TAKING_FORK, philo->index)
		|| philo->sim->num_philos == 1)
		return (pthread_mutex_unlock(first_fork), false);
	pthread_mutex_lock(second_fork);
	if (!print_log_message(philo->sim, LOG_TAKING_FORK, philo->index))
		return (pthread_mutex_unlock(first_fork),
			pthread_mutex_unlock(second_fork), false);
	return (true);
}

bool	eat_spaghetti(t_philo *philo)
{
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
