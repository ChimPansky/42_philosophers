/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_messages.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:05:55 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/12 11:56:34 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_MESSAGES_H
# define PH_MESSAGES_H

#include <stdbool.h>

# define ERRMSG_MALLOC "Memory Allocation Error"
# define ERRMSG_PTHREAD "Could not create thread"
# define ERRMSG_MUTEX "Could not create mutex"
# define ERRMSG_UNKNOWN "Unknown Error"
# define ERRMSG_ARGS_NOT_ENOUGH "Not enough arguments."
# define ERRMSG_ARGS_TOO_MANY "Too many arguments."
# define ERRMSG_ARG_NOT_INT "Argument is not an integer"

# define LOG_TAKING_FORK "has taken a fork"
# define LOG_EAT "is eating"
# define LOG_SLEEPING "is sleeping"
# define LOG_THINKING "is thinking"
# define LOG_DYING "died"


# define SUCCESS 0
# define FAILURE !SUCCESS

typedef enum e_errors
{
	ERRNO_MALLOC,
	ERRNO_PTHREAD,
	ERRNO_MUTEX,
	ERRNO_ARGS_NOT_ENOUGH,
	ERRNO_ARGS_TOO_MANY,
	ERRNO_ARG_NOT_INT,
	ERRNO_COUNT
}			t_errors;

#endif
