/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:48:06 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/14 09:58:45 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;

	if (!len && !big)
		return (NULL);
	llen = ft_strlen(little);
	if (!llen)
		return ((char *)big);
	while (*big && len >= llen)
	{
		if (ft_strncmp(little, big, llen) == 0)
			return ((char *)big);
		len--;
		big++;
	}
	return (NULL);
}
