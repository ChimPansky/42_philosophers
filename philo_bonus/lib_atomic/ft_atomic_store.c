/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atomic_store.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:03:32 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/13 14:29:35 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic.h"

void	ft_atomic_int_store(t_ft_atomic_int *atomic, int val)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val = val;
	pthread_mutex_unlock(&atomic->mtx);
}

void	ft_atomic_long_store(t_ft_atomic_long *atomic, long val)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val = val;
	pthread_mutex_unlock(&atomic->mtx);
}

void	ft_atomic_bool_store(t_ft_atomic_bool *atomic, bool val)
{
	pthread_mutex_lock(&atomic->mtx);
	atomic->val = val;
	pthread_mutex_unlock(&atomic->mtx);
}
