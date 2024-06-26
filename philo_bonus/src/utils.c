/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:22:41 by tkasbari          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:05 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(char *string)
{
	unsigned long	result;
	int				sign_multiplier;

	result = 0;
	sign_multiplier = 1;
	while ((*string == 32 || (*string >= 9 && *string <= 13)))
		string++;
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			sign_multiplier = -1;
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		result = result * 10 + *string - '0';
		string++;
	}
	if (sign_multiplier == -1 && result == (LONG_MAX + 1lu))
		return (LONG_MIN);
	return ((long)result * sign_multiplier);
}

int	ft_atoi(char *string)
{
	unsigned int	result;
	int				sign_multiplier;

	result = 0;
	sign_multiplier = 1;
	while ((*string == 32 || (*string >= 9 && *string <= 13)))
		string++;
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			sign_multiplier = -1;
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		result = result * 10 + *string - '0';
		string++;
	}
	if (sign_multiplier == -1 && result == (INT_MAX + 1u))
		return (INT_MIN);
	return ((int)result * sign_multiplier);
}

bool	ft_str_isnum(char *string)
{
	if (*string == '-' || *string == '+')
		string++;
	if (!*string)
		return (false);
	while (*string)
	{
		if (*string < '0' || *string > '9')
			return (false);
		string++;
	}
	return (true);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	bytes_written;

	bytes_written = 0;
	if (!s)
		return ;
	bytes_written = write(fd, s, ft_strlen(s));
	(void)bytes_written;
}
