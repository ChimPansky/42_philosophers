/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atomic_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:03:36 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 12:28:40 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic.h"

int	ft_atomic_int_load(t_ft_atomic_int *atomic)
{
	int	val;

	pthread_mutex_lock(&atomic->mtx);
	val = atomic->val;
	pthread_mutex_unlock(&atomic->mtx);
	return (val);
}

long	ft_atomic_long_load(t_ft_atomic_long *atomic)
{
	long	val;

	pthread_mutex_lock(&atomic->mtx);
	val = atomic->val;
	pthread_mutex_unlock(&atomic->mtx);
	return (val);
}

bool	ft_atomic_bool_load(t_ft_atomic_bool *atomic)
{
	bool	val;

	pthread_mutex_lock(&atomic->mtx);
	val = atomic->val;
	pthread_mutex_unlock(&atomic->mtx);
	return (val);
}
