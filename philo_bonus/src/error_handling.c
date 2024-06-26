/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:39:06 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/18 18:37:54 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static char	*ph_strerror(int error_nr)
// {
// 	char	error_messages[][ERRMSG_MAX_LEN] = {
// 		ERRMSG_MALLOC,
// 		ERRMSG_PTHREAD,
// 		ERRMSG_MUTEX,
// 		ERRMSG_ARGS_NOT_ENOUGH,
// 		ERRMSG_ARGS_TOO_MANY,
// 		ERRMSG_ARG_NOT_NUM,
// 		ERRMSG_ARG_NEG,
// 		ERRMSG_UNKNOWN
// 	};
// 	return (error_messages[error_nr]);
// 	if (error_nr == ERRNO_MALLOC)
// 		return (ERRMSG_MALLOC);
// 	else if (error_nr == ERRNO_ARGS_NOT_ENOUGH)
// 		return (ERRMSG_ARGS_NOT_ENOUGH);
// 	else
// 		return (ERRMSG_UNKNOWN);
// }
int	ph_perror(int error_nr, char *error_info)
{
	const char	error_messages[][ERRMSG_MAX_LEN] = {
		ERRMSG_MALLOC,
		ERRMSG_PTHREAD,
		ERRMSG_MUTEX_CREATE,
		ERRMSG_MUTEX_DESTROY,
		ERRMSG_ARGS_NOT_ENOUGH,
		ERRMSG_ARGS_TOO_MANY,
		ERRMSG_ARG_NOT_NUM,
		ERRMSG_ARG_NOT_INT,
		ERRMSG_ARG_NOT_LONG,
		ERRMSG_ARG_NO_PHILO,
		ERRMSG_SEM_OPEN,
		ERRMSG_SEM_CLOSE,
		ERRMSG_FORK,
		ERRMSG_UNKNOWN
	};

	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (error_info)
	{
		ft_putstr_fd(error_info, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)error_messages[error_nr], STDERR_FILENO);
	return (ft_putstr_fd("\n", STDERR_FILENO), error_nr);
}
