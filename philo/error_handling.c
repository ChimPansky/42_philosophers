/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:39:06 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/11 23:45:37 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	ph_error(int error_nr, char *error_info)
{
	if (error_info)
	{
		ft_putstr_fd(error_info, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	


}
