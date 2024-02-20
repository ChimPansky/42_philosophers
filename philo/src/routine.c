/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:24:16 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 12:39:49 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_end(t_simulation *sim)
{
	if (!ft_atomic_bool_load(&sim->all_are_alive)
		|| ft_atomic_bool_load(&sim->all_had_enough_meals))
		return (true);
	return (false);
}

static bool	think_thoroughly(t_philo *philo)
{
	usleep(1);
	if (!print_log_message(philo->sim, LOG_THINKING, philo->index))
		return (false);
	usleep(philo->sim->time_to_think * USEC_MULTIPLIER);
	return (true);
}

static bool	sleep_well(t_philo *philo)
{
	usleep(1);
	if (!print_log_message(philo->sim, LOG_SLEEPING, philo->index))
		return (false);
	usleep(philo->sim->time_to_sleep * USEC_MULTIPLIER);
	return (true);
}

static void	synchronise_start_time(t_philo *philo)
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
	while (true && philo->sim->number_of_times_each_philosopher_must_eat != 0)
	{
		if (!eat_spaghetti(philo) || simulation_end(philo->sim))
			break ;
		if (!sleep_well(philo) || simulation_end(philo->sim))
			break ;
		if (!think_thoroughly(philo) || simulation_end(philo->sim))
			break ;
		if (ft_atomic_bool_load(&philo->had_enough_meals) == true)
			break ;
	}
	return ((void *)philo);
}
