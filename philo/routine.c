/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:24:16 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/19 13:24:07 by tkasbari         ###   ########.fr       */
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
static bool	take_fork(t_philo *philo, pthread_mutex_t *mx_fork, int f_ind)
{
	pthread_mutex_lock(mx_fork);
	dprintf(philo->sim->log_fd, "P%d ABOUT TO TAKE FORK %d\n", philo->index + 1, f_ind + 1);
	return (print_log_message(philo->sim, LOG_TAKING_FORK, philo->index));
}

static bool	eat_spaghetti(t_philo *philo)
{
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	bool			could_take_fork;

	could_take_fork = false;

	long	b_o_last_meal;

	int	r_ind = philo->index;
	int l_ind = (philo->index + philo->sim->num_philos - 1)	% philo->sim->num_philos;
	right_fork = &philo->sim->fork_guards[philo->index];
	left_fork = &philo->sim->fork_guards[
		(philo->index + philo->sim->num_philos - 1)	% philo->sim->num_philos];
	if (philo->index % 2 == 0)
		could_take_fork = take_fork(philo, right_fork, r_ind);
	else
		could_take_fork = take_fork(philo, left_fork, l_ind);
	if (!could_take_fork || simulation_end(philo->sim))	// put down fork?
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		return (dprintf(philo->sim->log_fd,"P%d couldnt take first fork\n", philo->index + 1), false);
	}
	if (philo->sim->num_philos == 1)
	{
		pthread_mutex_unlock(right_fork);
		return (false);
	}
	if (philo->index % 2 == 0)
		could_take_fork = could_take_fork && take_fork(philo, left_fork, l_ind);
	else
		could_take_fork = could_take_fork && take_fork(philo, right_fork, r_ind);
	if (simulation_end(philo->sim))	// put down forks?
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
			return (dprintf(philo->sim->log_fd,"P%d couldnt take second fork\n", philo->index + 1), false);
	}


	ft_atomic_long_store(&philo->time_of_beginning_of_last_meal,
		get_current_time_usec());
	if (!print_log_message(philo->sim, LOG_EAT, philo->index))
		return (false);
	usleep(philo->sim->time_to_eat * USEC_MULTIPLIER);
	ft_atomic_int_fetch_add(&philo->number_of_meals_eaten, 1);
	if (philo->sim->number_of_times_each_philosopher_must_eat != -1
		&& ft_atomic_int_load(&philo->number_of_meals_eaten)
		>= philo->sim->number_of_times_each_philosopher_must_eat)
		ft_atomic_bool_store(&philo->had_enough_meals, true);
	pthread_mutex_unlock(right_fork);
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
