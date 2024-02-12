#include "philo.h"

// checks if str can be converted to int and if yes,
// stores the conversion in target
// returns SUCCESS/FAILURE
// int	convert_str_to_int(char *str_to_convert, int *target)
// {

// 	return (SUCCESS);
// }

size_t	ft_strlen(const char	*s)
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
