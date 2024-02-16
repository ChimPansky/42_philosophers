/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atomic_fetch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:03:40 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/13 14:29:16 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic.h"

void	ft_atomic_int_fetch_add(t_ft_atomic_int *atomic, int val)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val += val;
	pthread_mutex_unlock(&atomic->mtx);
}

void	ft_atomic_long_fetch_add(t_ft_atomic_long *atomic, long val)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val += val;
	pthread_mutex_unlock(&atomic->mtx);
}

void	ft_atomic_int_fetch_sub(t_ft_atomic_int *atomic, int val)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val -= val;
	pthread_mutex_unlock(&atomic->mtx);
}

void	ft_atomic_long_fetch_sub(t_ft_atomic_long *atomic, long val)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val -= val;
	pthread_mutex_unlock(&atomic->mtx);
}

void	ft_atomic_bool_fetch_toggle(t_ft_atomic_bool *atomic)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val = !atomic->val;
	pthread_mutex_unlock(&atomic->mtx);
}
