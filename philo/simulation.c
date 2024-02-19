/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:30:38 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/13 15:17:16 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic/lib_atomic.h"
#include "philo.h"
#include <stdbool.h>

bool	print_log_message(t_simulation *sim, char *log_event, int philo_ind)
{
	pthread_mutex_lock(&sim->logging_guard);
	if (simulation_end(sim))	// TODO: unlock?
	{
		pthread_mutex_unlock(&sim->logging_guard);
		return (false);
	}
	printf("%ld P%d %s\n",
		get_current_sim_time(sim), philo_ind + 1, log_event);
	pthread_mutex_unlock(&sim->logging_guard);
	return (true);
}

bool	simulation_end(t_simulation *sim)
{
	if (!ft_atomic_bool_load(&sim->all_are_alive)
		|| ft_atomic_bool_load(&sim->all_had_enough_meals))
		return (true);
	return (false);
}

static void join_and_destroy_philos(t_philo *philos, int num_philos)
{
	int	i;

	i = 0;
	if (!philos)
		return ;
	while (i < num_philos)
	{
		pthread_join(philos[i].pthread, NULL);
		i++;
	}
	free(philos);
}

static int	init_philos(t_philo **philos, int num_philos, t_simulation *sim)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * num_philos);
	if (!*philos)
		return (ph_perror(ERRNO_MALLOC, "init_philos"), FAILURE);
	while (i < num_philos)
	{
		if (pthread_create(&(*philos)[i].pthread, NULL,
			&routine_eat_sleep_think, (void *)&(*philos)[i]) != SUCCESS)
			return (ph_perror(ERRNO_PTHREAD, "init_philos"),
				join_and_destroy_philos(*philos, i - 1), FAILURE);
		(*philos)[i].index = i;
		ft_atomic_int_init(&(*philos)[i].number_of_meals_eaten, 0);// TODO: protect this
		ft_atomic_long_init(&(*philos)[i].time_of_beginning_of_last_meal, 0); // protect this
		ft_atomic_bool_init(&(*philos)[i].sim_has_ended, false); // protect this
		ft_atomic_bool_init(&(*philos)[i].had_enough_meals, false); // protect this
		(*philos)[i].sim = sim;
		i++;
	}
	return (SUCCESS);
}

int	run_simulation(t_simulation *sim)
{
	t_philo			*philos;

	if (init_philos(&philos, sim->num_philos, sim) != SUCCESS)
		return (FAILURE);
	usleep((sim->time_to_die / 2 * USEC_MULTIPLIER));
	while (!simulation_end(sim))
	{
		usleep(1);
		update_sim_end_conditions(sim, philos);
	}
	int i = 0;
	while (i < sim->num_philos)
	{
		ft_atomic_bool_store(&philos[i].sim_has_ended, true);
		i++;
	}
	join_and_destroy_philos(philos, sim->num_philos);
	return (SUCCESS);
}
