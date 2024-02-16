/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atomic_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:49 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/13 14:29:22 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic.h"

int	ft_atomic_int_init(t_ft_atomic_int *atomic, int val)
{
	atomic->val = val;
	if (pthread_mutex_init(&atomic->mtx, NULL) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_atomic_long_init(t_ft_atomic_long *atomic, long val)
{
	atomic->val = val;
	return (pthread_mutex_init(&atomic->mtx, NULL));
}

int	ft_atomic_bool_init(t_ft_atomic_bool *atomic, bool val)
{
	atomic->val = val;
	return (pthread_mutex_init(&atomic->mtx, NULL));
}
