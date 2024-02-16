/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_atomic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:04:39 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/14 14:30:48 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_ATOMIC_H
# define LIB_ATOMIC_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <stdbool.h>

# define SUCCESS 0
# define FAILURE !SUCCESS

typedef struct s_ft_atomic_int
{
	int val;
	pthread_mutex_t mtx;
} 				t_ft_atomic_int;

typedef struct s_ft_atomic_long
{
	long val;
	pthread_mutex_t mtx;
} 				t_ft_atomic_long;

typedef struct s_ft_atomic_bool
{
	bool val;
	pthread_mutex_t mtx;
} 				t_ft_atomic_bool;

// ft_atomic_init.c
// these functions initialize the mutex and set the value of the atomic
int	ft_atomic_int_init(t_ft_atomic_int *atomic, int val);
int	ft_atomic_long_init(t_ft_atomic_long *atomic, long val);
int	ft_atomic_bool_init(t_ft_atomic_bool *atomic, bool val);

//ft_atomic_destroy.c
// these functions destroy the mutex
int	ft_atomic_int_destroy(t_ft_atomic_int *atomic);
int	ft_atomic_long_destroy(t_ft_atomic_long *atomic);
int	ft_atomic_bool_destroy(t_ft_atomic_bool *atomic);

// ft_atomic_load.c
// these functions only read from the atomic
int		ft_atomic_int_load(t_ft_atomic_int *atomic);
long	ft_atomic_long_load(t_ft_atomic_long *atomic);
bool	ft_atomic_bool_load(t_ft_atomic_bool *atomic);

// ft_atomic_store.c
// these functions only write to the atomic
void	ft_atomic_int_store(t_ft_atomic_int *atomic, int val);
void	ft_atomic_long_store(t_ft_atomic_long *atomic, long val);
void	ft_atomic_bool_store(t_ft_atomic_bool *atomic, bool val);


// ft_atomic_fetch.c
// these functions at the same time read from and write to the atomic
void	ft_atomic_int_fetch_add(t_ft_atomic_int *atomic, int val);
void	ft_atomic_long_fetch_add(t_ft_atomic_long *atomic, long val);
void	ft_atomic_int_fetch_sub(t_ft_atomic_int *atomic, int val);
void	ft_atomic_long_fetch_sub(t_ft_atomic_long *atomic, long val);
void	ft_atomic_bool_fetch_toggle(t_ft_atomic_bool *atomic);

#endif
