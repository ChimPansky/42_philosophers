/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atomic_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:03:21 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/13 14:28:58 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_atomic.h"

int	ft_atomic_int_destroy(t_ft_atomic_int *atomic)
{
	return (pthread_mutex_destroy(&atomic->mtx));
}

int	ft_atomic_long_destroy(t_ft_atomic_long *atomic)
{
	return (pthread_mutex_destroy(&atomic->mtx));
}

int	ft_atomic_bool_destroy(t_ft_atomic_bool *atomic)
{
	return (pthread_mutex_destroy(&atomic->mtx));
}
