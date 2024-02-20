/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:39:06 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 12:27:41 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_perror(int error_nr, char *error_info)
{
	const char	error_messages[][ERRMSG_MAX_LEN] = {
		ERRMSG_MALLOC,
		ERRMSG_PTHREAD,
		ERRMSG_MUTEX,
		ERRMSG_ARGS_NOT_ENOUGH,
		ERRMSG_ARGS_TOO_MANY,
		ERRMSG_ARG_NOT_NUM,
		ERRMSG_ARG_NOT_INT,
		ERRMSG_ARG_NOT_LONG,
		ERRMSG_ARG_NO_PHILO,
		ERRMSG_UNKNOWN
	};

	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (error_info)
	{
		ft_putstr_fd(error_info, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)error_messages[error_nr], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (error_nr);
}
