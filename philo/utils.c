#include "philo.h"

// checks if str can be converted to int and if yes,
// stores the conversion in target
// returns SUCCESS/FAILURE
// int	convert_str_to_int(char *str_to_convert, int *target)
// {

// 	return (SUCCESS);
// }
#include <limits.h>

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

int		ft_atoi(char *string)
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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i) && size && i < size - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (size)
		*(dst + i) = '\0';
	return (ft_strlen(src));
}
