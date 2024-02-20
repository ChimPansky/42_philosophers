/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:30:31 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:38 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <bits/types/struct_timeval.h>

long	get_current_time_ms(void)
{
	struct timeval	cur_time;
	long			cur_time_ms;

	gettimeofday(&cur_time, NULL);
	cur_time_ms = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	return (cur_time_ms);
}

long	get_current_time_usec(void)
{
	struct timeval	cur_time;
	long			cur_time_usec;

	gettimeofday(&cur_time, NULL);
	cur_time_usec = cur_time.tv_sec * 1000000
		+ cur_time.tv_usec;
	return (cur_time_usec);
}

long	get_current_sim_time(t_simulation *sim)
{
	return ((get_current_time_usec() - sim->start_time) / USEC_MULTIPLIER);
}
