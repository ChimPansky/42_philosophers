/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_messages.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/16 17:57:50 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_MESSAGES_H
# define PH_MESSAGES_H

# define ERRMSG_MAX_LEN 50

# define ERRMSG_MALLOC "Memory Allocation Error"
# define ERRMSG_PTHREAD "Could not create thread"
# define ERRMSG_MUTEX_CREATE "Could not create mutex"
# define ERRMSG_MUTEX_DESTROY "Could not destroy mutex"
# define ERRMSG_ARGS_NOT_ENOUGH "Not enough arguments"
# define ERRMSG_ARGS_TOO_MANY "Too many arguments"
# define ERRMSG_ARG_NOT_NUM "Arguments have to be numeric"
# define ERRMSG_ARG_NOT_INT "Argument must be a positive integer"
# define ERRMSG_ARG_NOT_LONG "Argument must be a positive long integer"
# define ERRMSG_ARG_NO_PHILO "There has to be at least 1 philosopher"
# define ERRMSG_SEM_OPEN "Could not open semaphore"
# define ERRMSG_SEM_CLOSE "Could not close semaphore"
# define ERRMSG_FORK "Could not create child process"

# define ERRMSG_UNKNOWN "Unknown Error"

# define SUCCESS 0
# define FAILURE !SUCCESS

typedef enum e_errors
{
	ERRNO_MALLOC,
	ERRNO_PTHREAD,
	ERRNO_MUTEX_CREATE,
	ERRNO_MUTEX_DESTROY,
	ERRNO_ARGS_NOT_ENOUGH,
	ERRNO_ARGS_TOO_MANY,
	ERRNO_ARG_NOT_NUM,
	ERRNO_ARG_NOT_INT,
	ERRNO_ARG_NOT_LONG,
	ERRNO_ARG_NO_PHILO,
	ERRNO_SEM_OPEN,
	ERRNO_SEM_DESTROY,
	ERRNO_FORK,
	ERRNO_UNKNOWN,
	ERRNO_COUNT
}			t_errors;

#endif
