/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:06:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/12 13:17:25 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_messages.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>




/*allowed functions:
memset,
printf, write,
malloc,free,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock
*/

// int	read_and_validate_arguments(t_simulation *simulation, int argc, char **argv)
// {
// 	if (argc < 5)
// 		return (ft_putstr_fd("ERR_ARGS_NOT_ENOUGH", STDOUT_FILENO), FAILURE);
// 	if (argc > 6)
// 		return (ft_putstr_fd("ERR_ARGS_NOT_ENOUGH", STDOUT_FILENO), FAILURE);
// 	if (convert_str_to_int(argv[1], &simulation->num_philos) != SUCCESS)
// 		return (ph_error(ERR_ARG_NOT_INT, "number_of_philosophers"), FAILURE);

// 	return (SUCCESS);
// }

bool	has_someone_died(t_simulation *simulation)
{
	bool	someone_has_died;

	someone_has_died = false;
	pthread_mutex_lock(&simulation->mx_all_are_alive);
	if (!simulation->all_are_alive)
		someone_has_died = true;
	pthread_mutex_unlock(&simulation->mx_all_are_alive);
	return (someone_has_died);
}

void	update_meal_count(t_philo *philo)
{
	philo->number_of_meals_eaten++;
	if (philo->number_of_meals_eaten
		== philo->simulation->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->simulation->mx_num_philos_w_enough_meals);
		philo->simulation->num_philos_w_enough_meals++;
		pthread_mutex_lock(&philo->simulation->mx_num_philos_w_enough_meals);
	}
}

long	get_current_time_usec()
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_usec);
}

long	get_current_simulation_time(t_simulation *simulation)
{
	return (get_current_time_usec() - simulation->start_time);
}

void	print_log_message(pthread_mutex_t *mx_logging, char *log_event, long timestamp, int philo_nr)
{
	pthread_mutex_lock(mx_logging);
	printf("%ld %d %s\n", timestamp, philo_nr, log_event);
	pthread_mutex_unlock(mx_logging);
}

void	think_thoroughly(t_philo *philo)
{
	print_log_message(&philo->simulation->mx_logging, LOG_THINKING,
		get_current_simulation_time(philo->simulation), philo->index + 1);
	usleep(10 * USEC_MULTIPLIER);
}

void	sleep_well(t_philo *philo)
{
	print_log_message(&philo->simulation->mx_logging, LOG_SLEEPING,
		get_current_simulation_time(philo->simulation), philo->index + 1);
	usleep(philo->simulation->time_to_sleep * USEC_MULTIPLIER);
}
void	take_fork(t_philo *philo, pthread_mutex_t *mx_fork)
{
	pthread_mutex_lock(mx_fork);
	print_log_message(&philo->simulation->mx_logging, LOG_TAKING_FORK,
		get_current_simulation_time(philo->simulation), philo->index + 1);
}

void	eat_spaghetti(t_philo *philo)
{
	pthread_mutex_t *mx_right_fork;
	pthread_mutex_t *mx_left_fork;

	mx_right_fork = &philo->simulation->mx_forks[philo->index];
	mx_left_fork = &philo->simulation->mx_forks[(philo->index - 1)
					% philo->simulation->num_philos];
	if (philo->index % 2 == 0)
		take_fork(philo, mx_right_fork);
	else
		take_fork(philo, mx_left_fork);
	if (philo->index % 2 == 0)
		take_fork(philo, mx_left_fork);
	else
		take_fork(philo, mx_right_fork);
	philo->time_of_beginning_of_last_meal = get_current_simulation_time(
		philo->simulation);
	print_log_message(&philo->simulation->mx_logging, LOG_EAT,
		philo->time_of_beginning_of_last_meal, philo->index + 1);
	usleep(philo->simulation->time_to_eat * USEC_MULTIPLIER);
	pthread_mutex_unlock(mx_left_fork);
	pthread_mutex_unlock(mx_right_fork);
	update_meal_count(philo);
}
void	*routine_eat_sleep_think(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(true)
	{
		if (has_someone_died(philo->simulation))
			break;
		eat_spaghetti(philo);
		if (has_someone_died(philo->simulation))
			break ;
		sleep_well(philo);
		if (has_someone_died(philo->simulation))
			break ;
		think_thoroughly(philo);
	}
	return ((void*)philo);
}

bool	check_if_philo_is_alive(t_philo philo)
{
	long	cur_time;

	cur_time = get_current_simulation_time(philo.simulation);
	if ((cur_time - philo.time_of_beginning_of_last_meal) < philo.simulation->time_to_die)
	{
		pthread_mutex_lock(&philo.simulation->mx_all_are_alive);
		if (!philo.simulation->all_are_alive)
		{
			print_log_message(&philo.simulation->mx_logging,
				LOG_DYING, cur_time, philo.index + 1);
			philo.simulation->all_are_alive = false;
		}
		pthread_mutex_unlock(&philo.simulation->mx_all_are_alive);
		return (false);
	}
	return (true);
}
void	check_if_all_are_alive(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (philos->simulation)->num_philos)
	{
		if (!check_if_philo_is_alive(philos[i]))
			break;
		i++;
	}
}
bool	enough_meals_have_been_eaten(t_simulation simulation)
{
	if (simulation.number_of_times_each_philosopher_must_eat < 0)
		return (false);
	if (simulation.num_philos_w_enough_meals
		>= simulation.number_of_times_each_philosopher_must_eat)
		return (true);
	return (false);
}

void	init_simulation(t_simulation *simulation)
{
	simulation->num_philos = 2;
	simulation->time_to_die = 1000;
	simulation->time_to_eat = 400;
	simulation->time_to_sleep = 400;
	simulation->number_of_times_each_philosopher_must_eat = -1;
	simulation->num_philos_w_enough_meals = 0;
	simulation->all_are_alive = true;
	pthread_mutex_init(&simulation->mx_num_philos_w_enough_meals, NULL);
	pthread_mutex_init(&simulation->mx_all_are_alive, NULL);
	pthread_mutex_init(&simulation->mx_logging, NULL);
	simulation->start_time = get_current_time_usec();
}

int	init_forks(pthread_mutex_t *mx_forks, int num_philos)
{
	int	i;

	i = 0;
	mx_forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!mx_forks)
		return (ph_perror(ERRNO_MALLOC, "init_forks"));
	while (i < num_philos)
	{
		if (pthread_mutex_init(&mx_forks[i], NULL) != SUCCESS)
			return (ph_perror(ERRNO_MUTEX, "init_forks"));
		i++;
	}
	return (SUCCESS);
}

int	init_philos(t_philo *philos, t_simulation *simulation)
{
	int	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * simulation->num_philos);
	if (!philos)
		return (ph_perror(ERRNO_MALLOC, "init_philos"));
	while (i < simulation->num_philos)
	{
		if (pthread_create(&philos[i].pthread, NULL,
			&routine_eat_sleep_think, (void *)&philos[i]) != SUCCESS)
			return (ph_perror(ERRNO_PTHREAD, "init_philos"));
		philos[i].index = 0;
		philos[i].number_of_meals_eaten = 0;
		philos[i].time_of_beginning_of_last_meal = 0;
		philos[i].simulation = simulation;
		i++;
	}
	return (SUCCESS);
}
void	wait_for_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->simulation->num_philos)
	{
		pthread_join(philos[i].pthread, NULL);
		i++;
	}
}

void	destroy_forks(pthread_mutex_t *mx_forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&mx_forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;
	t_philo			*philos;

	init_simulation(&simulation);
	philos = NULL;
	(void)argc;
	(void)argv;
	// if (read_and_validate_arguments(&simulation, argc, argv) != SUCCESS)
	// 	return (FAILURE);

	printf("start_time: %ld\n\n", simulation.start_time);
	if (init_forks(simulation.mx_forks, simulation.num_philos) != SUCCESS)
		return (FAILURE);
	if (init_philos(philos, &simulation) != SUCCESS) //pthread_create();
		return (FAILURE);


	while (simulation.all_are_alive && !enough_meals_have_been_eaten(simulation))
	{
		check_if_all_are_alive(philos);
		usleep(5);
	}

	wait_for_philos(philos); //join_philos  pthread_join(); wait for threads to finish
	destroy_forks(simulation.mx_forks, simulation.num_philos); //pthread_mutex_destroy();
	free(simulation.mx_forks);
	free(philos);
	return (0);
}
