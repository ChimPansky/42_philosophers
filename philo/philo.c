/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:06:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/13 18:00:34 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



/*allowed functions:
memset,
printf, write,
malloc,free,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock
*/

static void	destroy_forks(t_simulation *sim)
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
	//ft_atomic_bool_destroy(&(*sim)->all_had_enough_meals);
	//ft_atomic_bool_destroy(&(*sim)->all_are_alive);
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
	(*sim)->all_are_alive = true;
	(*sim)->all_had_enough_meals = false;
	//& ft_atomic_bool_init(&(*sim)->all_had_enough_meals, false)
		//& ft_atomic_bool_init(&(*sim)->all_are_alive, true)) != SUCCESS)
	if (pthread_mutex_init(&(*sim)->logging_guard, NULL) != SUCCESS)
		return (ph_perror(ERRNO_MUTEX, "init_simulation"),
			destroy_simulation(sim), FAILURE);
	(*sim)->start_time = get_current_time_ms();
	(*sim)->fork_guards = NULL;
	return (SUCCESS);
}


static int	read_args_into_sim(t_simulation *sim, int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr_fd("ERR_ARGS_NOT_ENOUGH\n", STDOUT_FILENO), FAILURE);
	if (argc > 6)
		return (ft_putstr_fd("ERR_ARGS_NOT_ENOUGH\n", STDOUT_FILENO), FAILURE);
	sim->num_philos = atoi(argv[1]);
	sim->time_to_die = atoi(argv[2]);
	sim->time_to_eat = atoi(argv[3]);
	sim->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		sim->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		sim->number_of_times_each_philosopher_must_eat = -1;

	// if (convert_str_to_int(argv[1], &sim->num_philos) != SUCCESS)
	// 	return (ph_error(ERR_ARG_NOT_INT, "number_of_philosophers"), FAILURE);

	return (SUCCESS);
}



int	main(int argc, char **argv)
{
	t_simulation	*sim;

	if (init_simulation(&sim) != SUCCESS)
		return (FAILURE);
	if ((read_args_into_sim(sim, argc, argv) | init_forks(sim)) != SUCCESS)
		return (destroy_simulation(&sim), FAILURE);

	printf("start_time: %ld\n\n", sim->start_time);
	run_simulation(sim);



	destroy_simulation(&sim);
	return (0);
}
