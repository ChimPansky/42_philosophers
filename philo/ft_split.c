/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:48:06 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/16 13:03:57 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_split(char const *s, char c);
static int		ft_create_words(char **res, char *str, int wordc, char sep);
static char		**ft_free_result(char **res, int count);
static size_t	ft_count_words(char *str, char sep);

size_t	ft_count_words(char *str, char sep)
{
	size_t	count;
	int		start;

	count = 0;
	start = 1;
	while (*str)
	{
		if (*str == sep)
			start = 1;
		else
		{
			if (start)
				count++;
			start = 0;
		}
		str++;
	}
	return (count);
}

char	**ft_free_result(char **res, int count)
{
	while (count > 0)
	{
		if (res[--count])
			free(res[count]);
	}
	free(res);
	return (NULL);
}

int	ft_create_words(char **res, char *str, int wordc, char sep)
{
	int		i;
	size_t	wlen;

	i = 0;
	wlen = 0;
	while (i < wordc)
	{
		wlen = 0;
		while (*str == sep)
			str++;
		while (*str && *str != sep)
		{
			wlen++;
			str++;
		}
		res[i] = (char *)ft_calloc(sizeof(char), wlen + 1);
		if (!res[i])
		{
			ft_free_result(res, i);
			return (0);
		}
		ft_strlcpy(res[i++], (str - wlen), wlen + 1);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	size_t	wordc;
	char	**result;

	if (!s)
		return (NULL);
	str = (char *) s;
	wordc = ft_count_words(str, c);
	result = (char **)ft_calloc(sizeof(char *), wordc + 1);
	if (!result)
		return (NULL);
	if (!ft_create_words(result, str, wordc, c))
		return (NULL);
	result[wordc] = NULL;
	return (result);
}
