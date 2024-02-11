/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:48:06 by tkasbari          #+#    #+#             */
/*   Updated: 2023/09/15 10:37:46 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	left;
	size_t	right;
	size_t	len;

	left = 0;
	right = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = (char *)s1;
	while (ft_strchr(set, *(str + left)))
		left++;
	str = (char *)(s1 + ft_strlen(s1) - 1);
	while (ft_strrchr(set, *(str - right)))
		right++;
	if (left > len || right > len)
		len = 0;
	else
		len = len - left - right;
	return (ft_substr(s1, left, len));
}
