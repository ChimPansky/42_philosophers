/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:53:21 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/18 19:18:39 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic/lib_atomic.h"
#include "philo.h"
#include <stdbool.h>
#include <threads.h>

// checking all the philos for sim-end conditions in a loop
// if someone has died, set sim->all_are_alive to false
// if all philos have eaten enough, set sim->all_have_eaten to true


// bool	has_someone_died(t_simulation *sim)
// {
// 	bool	someone_has_died;

// 	someone_has_died = false;
// 	pthread_mutex_lock(&sim->mx_all_are_alive);
// 	if (!sim->all_are_alive)
// 		someone_has_died = true;
// 	pthread_mutex_unlock(&sim->mx_all_are_alive);
// 	return (someone_has_died);
// }
bool	check_if_philo_is_alive(t_philo philo, t_simulation *sim)
{
	if ((get_current_time_usec() -
		ft_atomic_long_load(&philo.time_of_beginning_of_last_meal))
		>= philo.sim->time_to_die * USEC_MULTIPLIER)
	{
		print_log_message(sim,
			LOG_DYING, philo.index + 1);
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
	int		num_philos_w_enough_meals;

	if (num_meals == -1)
		return (false);
	if (num_meals == 0)
		return (true);
	i = 0;
	num_philos_w_enough_meals = 0;
	while (i < num_philos)
	{
		if (ft_atomic_bool_load(&philos[i].had_enough_meals) == true)
			num_philos_w_enough_meals++;
		i++;
	}
	if (num_philos_w_enough_meals == num_philos)
		return (true);
	return (false);
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
