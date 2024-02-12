/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:06:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/12 17:52:01 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_messages.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>




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

long	get_current_time_ms()
{
	struct timeval	cur_time;
	long			cur_time_ms;

	gettimeofday(&cur_time, NULL);
	cur_time_ms = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	return (cur_time_ms);
}

long	get_current_simulation_time(t_simulation *simulation)
{
	//long	cur_time = get_current_time_ms();
	//long	dis_time = cur_time - simulation->start_time;

	//printf("sim_start_time: %ld\n", simulation->start_time);
	//printf("get_cur_sim_time: %ld\n", dis_time);
	//return (dis_time);
	return (get_current_time_ms() - simulation->start_time);
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
	usleep(50 * USEC_MULTIPLIER);
}
// the current_time is sometimes not calculated properly.
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

	printf("%ld TIME since last meal: \n", get_current_simulation_time(
		philo->simulation) - philo->time_of_beginning_of_last_meal);

	philo->time_of_beginning_of_last_meal = get_current_simulation_time(
		philo->simulation);
	print_log_message(&philo->simulation->mx_logging, LOG_EAT,
		philo->time_of_beginning_of_last_meal, philo->index + 1);
	usleep(philo->simulation->time_to_eat * USEC_MULTIPLIER);
	pthread_mutex_unlock(mx_right_fork);
	pthread_mutex_unlock(mx_left_fork);
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
	if ((cur_time - philo.time_of_beginning_of_last_meal) >= philo.simulation->time_to_die)
	{
		printf("CHECKING IF PHILO IS ALIVE\n");
		pthread_mutex_lock(&philo.simulation->mx_all_are_alive);
		if (philo.simulation->all_are_alive)
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
bool	are_all_alive(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->simulation->num_philos)
	{
		if (!check_if_philo_is_alive(philos[i]))
			return (false);
		i++;
	}
	return (true);
}
bool	have_enough_meals_been_eaten(t_simulation *simulation)
{
	bool	enough_meals_have_been_eaten;

	enough_meals_have_been_eaten = false;
	if (simulation->number_of_times_each_philosopher_must_eat < 0)
		return (false);
	pthread_mutex_lock(&simulation->mx_num_philos_w_enough_meals);
	if (simulation->num_philos_w_enough_meals >= simulation->num_philos)
		enough_meals_have_been_eaten = true;
	pthread_mutex_unlock(&simulation->mx_num_philos_w_enough_meals);
	return (enough_meals_have_been_eaten);
}

void	init_simulation(t_simulation *simulation)
{
	simulation->num_philos = 3;
	simulation->time_to_die = 1000;
	simulation->time_to_eat = 400;
	simulation->time_to_sleep = 400;
	simulation->number_of_times_each_philosopher_must_eat = -1;
	simulation->num_philos_w_enough_meals = 0;
	simulation->all_are_alive = true;
	pthread_mutex_init(&simulation->mx_num_philos_w_enough_meals, NULL);
	pthread_mutex_init(&simulation->mx_all_are_alive, NULL);
	pthread_mutex_init(&simulation->mx_logging, NULL);
	simulation->start_time = get_current_time_ms();
}

pthread_mutex_t	*init_forks(int num_philos)
{
	int	i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!forks)
		return (ph_perror(ERRNO_MALLOC, "init_forks"), NULL);
	while (i < num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != SUCCESS)
			return (ph_perror(ERRNO_MUTEX, "init_forks"), NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_simulation *simulation)
{
	int	i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * simulation->num_philos);
	if (!philos)
		return (ph_perror(ERRNO_MALLOC, "init_philos"), NULL);
	while (i < simulation->num_philos)
	{
		if (pthread_create(&(philos[i]).pthread, NULL,
			&routine_eat_sleep_think, (void *)&(philos)[i]) != SUCCESS)
			return (ph_perror(ERRNO_PTHREAD, "init_philos"), NULL);
		philos[i].index = i;
		philos[i].number_of_meals_eaten = 0;
		philos[i].time_of_beginning_of_last_meal = 0;
		philos[i].simulation = simulation;
		i++;
	}
	return (philos);
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
	free(mx_forks);
}

int	main(int argc, char **argv)
{
	t_simulation	*simulation;
	t_philo			*philos;

	philos = NULL;
	(void)argc;
	(void)argv;
	// if (read_and_validate_arguments(&simulation, argc, argv) != SUCCESS)
	// 	return (FAILURE);

	simulation = malloc(sizeof(t_simulation));
	init_simulation(simulation);
	printf("start_time: %ld\n\n", simulation->start_time);
	simulation->mx_forks = init_forks(simulation->num_philos);
	if (!simulation->mx_forks)
		return (FAILURE);
	philos = init_philos(simulation);
	if (!philos)
		return (destroy_forks(simulation->mx_forks, simulation->num_philos),
			 FAILURE);

	while (are_all_alive(philos) && !have_enough_meals_been_eaten(simulation))
		usleep(5);

	wait_for_philos(philos); //join_philos  pthread_join(); wait for threads to finish
	destroy_forks(simulation->mx_forks, simulation->num_philos); //pthread_mutex_destroy();
	free(simulation->mx_forks);
	free(philos);
	free(simulation);
	return (0);
}
