/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:06:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/12 00:42:41 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>


/*allowed functions:
memset,
printf, write,
malloc,free,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock
*/

int	read_and_validate_arguments(t_simulation *simulation, int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr_fd("ERR_ARGS_NOT_ENOUGH", STDOUT_FILENO), FAILURE);
	if (argc > 6)
		return (ft_putstr_fd("ERR_ARGS_NOT_ENOUGH", STDOUT_FILENO), FAILURE);
	if (convert_str_to_int(argv[1], &simulation->num_philos) != SUCCESS)
		return (ph_error(ERR_ARG_NOT_INT, "number_of_philosophers"), FAILURE);

	return (SUCCESS);
}

void	eat_spaghetti(void)
{
	if (even)
		lock_left_fork;
		lock_right_fork;
		set_time_of_beginning_of_last_meal();
		usleep(time_to_eat * 1000);
		unlock_left_fork;
		unlock_right_fork;
	else (odd)
		lock_right_fork;
		lock_left_fork;
		set_time_of_beginning_of_last_meal();
		usleep(time_to_eat * 1000);
		unlock_right_fork;
		unlock_left_fork;
}
void	*routine_eat_sleep_think(void *arg)
{
	while(simulation.all_are_alive)
	{
		eat_spaghetti();
		if (simulation.all_are_alive)
			sleep();
		if (simulation.all_are_alive)
			think();
	}
}
bool	philo_is_alive(t_philo philo)
{
	if ((get_current_time() - philo.time_of_beginning_of_last_meal) < simulation.time_to_die)
	{
		lock simulation.all_are_alive;
		if (simulation.all_are_alive)
		{
			print "philo has died";
			simulation.all_are_alive = false;
		}
		unlock simulation.all_are_alive;
		return (false);
	}
	return (true);
}
bool	all_are_alive()
{
	while (*philos)
	{
		if (!philo_is_alive(*philos))
			return (false);
		philos++;
	}
	return (true);
}
bool	enough_meals_have_been_eaten()
{
	return (false);
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;
	pthread_t		*th_philos;
	pthread_mutex_t	*mx_forks;

	if (read_and_validate_arguments(&simulation, argc, argv) != SUCCESS)
		return (FAILURE);
	init_forks(); //pthread_mutex_init();
	init_philos(); //pthread_create(); pthread_create(&routine_eat_sleep_think);


	while (all_are_alive() && !enough_meals_have_been_eaten())
		usleep(5);

	wait_for_philos(); //join_philos  pthread_join(); wait for threads to finish
	destroy_forks(); //pthread_mutex_destroy();


	return (0);
}
