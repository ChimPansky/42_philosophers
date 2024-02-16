/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:06:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/16 11:17:50 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(t_simulation *sim) // TODO: destroy atomics?
{
	int	i;

	i = 0;
	if (!sim->fork_guards)
		return ;
	while (i < sim->num_philos)
	{
		pthread_mutex_destroy(&sim->fork_guards[i]);
		i++;
	}
	free(sim->fork_guards);
}
static int	init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->fork_guards = malloc(sizeof(pthread_mutex_t) * sim->num_philos);
	if (!sim->fork_guards)
		return (ph_perror(ERRNO_MALLOC, "init_forks"), FAILURE);
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&sim->fork_guards[i], NULL) != SUCCESS)
			return (ph_perror(ERRNO_MUTEX, "init_forks"), FAILURE);
		i++;
	}
	return (SUCCESS);
}
static void	destroy_simulation(t_simulation **sim)
{
	destroy_forks(*sim);
	pthread_mutex_destroy(&(*sim)->logging_guard);
	free(*sim);
}

static int	init_simulation(t_simulation **sim)
{
	*sim = malloc(sizeof(t_simulation));
	if (!*sim)
		return (ph_perror(ERRNO_MALLOC, "init_simulation"), FAILURE);
	(*sim)->num_philos = 0;
	(*sim)->time_to_die = 0;
	(*sim)->time_to_eat = 0;
	(*sim)->time_to_sleep = 0;
	(*sim)->number_of_times_each_philosopher_must_eat = -1;
	if ((ft_atomic_bool_init(&(*sim)->all_had_enough_meals, false)
		& ft_atomic_bool_init(&(*sim)->all_are_alive, true)
		& pthread_mutex_init(&(*sim)->logging_guard, NULL)) != SUCCESS)
		return (ph_perror(ERRNO_MUTEX, "init_simulation"),
			destroy_simulation(sim), FAILURE);
	(*sim)->start_time = get_current_time_ms();
	(*sim)->fork_guards = NULL;
	(*sim)->log_fd = open("debug.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644); // TODO remove
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_simulation	*sim;

	if (init_simulation(&sim) != SUCCESS)
		return (FAILURE);
	if ((read_args_into_sim(sim, argc, argv) != SUCCESS
		|| init_forks(sim)) != SUCCESS)
		return (destroy_simulation(&sim), FAILURE);
	dprintf(sim->log_fd, "start_time: %ld\n\n", sim->start_time);	// TODO remove
	run_simulation(sim);
	destroy_simulation(&sim);
	return (0);
}
