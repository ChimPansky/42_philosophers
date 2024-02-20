/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:53:21 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 12:27:03 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_if_philo_is_alive(t_philo philo, t_simulation *sim)
{
	if ((get_current_time_usec()
			- ft_atomic_long_load(&philo.time_of_beginning_of_last_meal))
		>= philo.sim->time_to_die * USEC_MULTIPLIER)
	{
		print_log_message(sim, LOG_DYING, philo.index);
		return (false);
	}
	return (true);
}

bool	are_all_alive(t_philo *philos, t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (!check_if_philo_is_alive(philos[i], sim))
			return (false);
		i++;
	}
	return (true);
}

bool	have_enough_meals_been_eaten(t_philo *philos, int num_philos,
		int num_meals)
{
	int		i;

	if (num_meals == -1)
		return (false);
	if (num_meals == 0)
		return (true);
	i = 0;
	while (i < num_philos)
		if (ft_atomic_bool_load(&philos[i++].had_enough_meals) == false)
			return (false);
	return (true);
}

void	update_sim_end_conditions(t_simulation *sim, t_philo *philos)
{
	if (have_enough_meals_been_eaten(philos, sim->num_philos,
			sim->number_of_times_each_philosopher_must_eat))
	{
		ft_atomic_bool_store(&sim->all_had_enough_meals, true);
		return ;
	}
	if (!are_all_alive(philos, sim))
		ft_atomic_bool_store(&sim->all_are_alive, false);
}
